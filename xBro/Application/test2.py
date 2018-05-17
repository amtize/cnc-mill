import wx
import os
from calculations import *
from wx.lib.pubsub import pub


class StartFrame(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title=title, size=(1000,500))
        #self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE)
        self.CreateStatusBar() # A StatusBar in the bottom of the window

        self.layout()

        # Setting up the menu.
        filemenu= wx.Menu()

        # wx.ID_ABOUT and wx.ID_EXIT are standard ids provided by wxWidgets.
        menuOpen = filemenu.Append(wx.ID_OPEN, "Open", "Open a picture.")
        menuAbout = filemenu.Append(wx.ID_ABOUT, "&About"," Information about this program")
        menuExit = filemenu.Append(wx.ID_EXIT,"E&xit"," Terminate the program")

        # Creating the menubar.
        menuBar = wx.MenuBar()
        menuBar.Append(filemenu,"&File") # Adding the "filemenu" to the MenuBar
        self.SetMenuBar(menuBar)  # Adding the MenuBar to the Frame content.

        # Set events.
        self.Bind(wx.EVT_MENU, self.OnAbout, menuAbout)
        self.Bind(wx.EVT_MENU, self.OnExit, menuExit)
        self.Bind(wx.EVT_MENU, self.OnOpen, menuOpen)

        self.Show(True)

    def OnOpen(self,e):
        self.dirname = ''
        dlg = wx.FileDialog(self, "Choose a file", self.dirname, "", "*.png", wx.FD_OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename()
            self.dirname = dlg.GetDirectory()
            f = open(os.path.join(self.dirname, self.filename), 'r')
            self.control.SetValue(f.read())
            f.close()
        dlg.Destroy()

    def OnAbout(self,e):
        # A message dialog box with an OK button. wx.OK is a standard ID in wxWidgets.
        dlg = wx.MessageDialog( self, "A small text editor", "About Sample Editor", wx.OK)
        dlg.ShowModal() # Show it
        dlg.Destroy() # finally destroy it when finished.

    def OnExit(self,e):
        self.Close(True)  # Close the frame.

    def layout(self):
        """
        Layout the widgets on the panel
        """

        self.mainSizer = wx.BoxSizer(wx.VERTICAL)
        lblSizer = wx.BoxSizer(wx.VERTICAL)

        lblData = [("Precision    (um): ", lblSizer, 100),
                   ("Width of bit (mm): ", lblSizer, 10)]
        for data in lblData:
            label, sizer, default = data
            self.lblBuilder(label, sizer, default)

        btnSizer = wx.BoxSizer(wx.VERTICAL)

        btnData = [("Previous", btnSizer, self.onPrevious, wx.Size(100,25)),
                   ("Parse image", btnSizer, self.OnOpenImage, wx.Size(200,50)),
                   ("Next", btnSizer, self.onNext, wx.Size(100,25))]
        for data in btnData:
            label, sizer, handler, size = data
            self.btnBuilder(label, sizer, handler, size)

        self.mainSizer.Add(lblSizer, 0, wx.CENTER)
        self.mainSizer.AddSpacer(50)
        self.mainSizer.Add(btnSizer, 0, wx.CENTER)
        self.SetSizer(self.mainSizer)

    def lblBuilder(self, label, sizer, default):
        tempSizer = wx.BoxSizer(wx.HORIZONTAL)
        label = wx.StaticText(self, label=label)
        textCtrl = wx.TextCtrl(self, value=str(default))
        tempSizer.Add(label, 0, wx.ALL|wx.CENTER, 5)
        tempSizer.Add(textCtrl, 0, wx.ALL|wx.CENTER, 5)

        sizer.Add(tempSizer, 0, wx.ALL|wx.CENTER, 5)


    #----------------------------------------------------------------------
    def btnBuilder(self, label, sizer, handler, size):
        """
        Builds a button, binds it to an event handler and adds it to a sizer
        """
        btn = wx.Button(self, label=label, size=size)
        btn.Bind(wx.EVT_BUTTON, handler)
        sizer.Add(btn, 0, wx.ALL|wx.CENTER, 5)

    #----------------------------------------------------------------------
    def loadImage(self, image):
        """"""
        image_name = os.path.basename(image)
        img = wx.Image(image, wx.BITMAP_TYPE_ANY)
        # scale the image, preserving the aspect ratio
        W = img.GetWidth()
        H = img.GetHeight()
        if W > H:
            NewW = self.photoMaxSize
            NewH = self.photoMaxSize * H / W
        else:
            NewH = self.photoMaxSize
            NewW = self.photoMaxSize * W / H
        img = img.Scale(NewW,NewH)

        self.imageCtrl.SetBitmap(wx.BitmapFromImage(img))
        self.imageLabel.SetLabel(image_name)
        self.Refresh()
        pub.sendMessage("resize", "")

    #----------------------------------------------------------------------
    def nextPicture(self):
        """
        Loads the next picture in the directory
        """
        if self.currentPicture == self.totalPictures-1:
            self.currentPicture = 0
        else:
            self.currentPicture += 1
        self.loadImage(self.picPaths[self.currentPicture])

    #----------------------------------------------------------------------
    def previousPicture(self):
        """
        Displays the previous picture in the directory
        """
        if self.currentPicture == 0:
            self.currentPicture = self.totalPictures - 1
        else:
            self.currentPicture -= 1
        self.loadImage(self.picPaths[self.currentPicture])

    #----------------------------------------------------------------------
    def update(self, event):
        """
        Called when the slideTimer's timer event fires. Loads the next
        picture from the folder by calling th nextPicture method
        """
        self.nextPicture()

    #----------------------------------------------------------------------
    def updateImages(self, msg):
        """
        Updates the picPaths list to contain the current folder's images
        """
        self.picPaths = msg.data
        self.totalPictures = len(self.picPaths)
        self.loadImage(self.picPaths[0])

    #----------------------------------------------------------------------
    def onNext(self, event):
        """
        Calls the nextPicture method
        """
        self.nextPicture()

    #----------------------------------------------------------------------
    def onPrevious(self, event):
        """
        Calls the previousPicture method
        """
        self.previousPicture()

    #----------------------------------------------------------------------
    def OnOpenImage(self, event):
        self.dirname = ''
        dlg = wx.FileDialog(self, "Choose a file", self.dirname, "", "*.png", wx.FD_OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename()
            self.dirname = dlg.GetDirectory()
            self.Destroy()
            self.Frame = ImgFrame(wx.Image(self.dirname + '/' + self.filename, wx.BITMAP_TYPE_PNG), dlg.GetPath())
        dlg.Destroy()


class ImgFrame(wx.Frame):
    def __init__(self,image,path,parent = None, id=-1,pos=wx.DefaultPosition,title='Hello, wxPytho!'):
        self.original = image.ConvertToBitmap()
        size = self.original.GetWidth(), self.original.GetHeight() + 200
        wx.Frame.__init__(self, parent, id, title, pos, size)
        self.bmp = wx.StaticBitmap(parent=self, bitmap=self.original)

        self.mainSizer = wx.BoxSizer(wx.VERTICAL)

        self.mask = CalculateMask(path)         #path
        self.hough = CalculateHoughLines(self.mask)  #path


        btnSizer = wx.BoxSizer(wx.HORIZONTAL)

        btnEdges = wx.Button(self, label="View edges")
        btnEdges.Bind(wx.EVT_BUTTON, self.OnViewEdges)
        btnMask = wx.Button(self, label="View mask")
        btnMask.Bind(wx.EVT_BUTTON, self.OnViewMask)
        btnPath = wx.Button(self, label="View path")
        btnPath.Bind(wx.EVT_BUTTON, self.OnViewPath)
        btnOriginal = wx.Button(self, label="View original")
        btnOriginal.Bind(wx.EVT_BUTTON, self.OnViewOriginal)

        btnSizer.Add(btnEdges, 0, wx.ALL|wx.CENTER, 5)
        btnSizer.Add(btnMask, 0, wx.ALL|wx.CENTER, 5)
        btnSizer.Add(btnPath, 0, wx.ALL|wx.CENTER, 5)
        btnSizer.Add(btnOriginal, 0, wx.ALL|wx.CENTER, 5)

        btnMake = wx.Button(self, label="Make", size=wx.Size(200,50))
        btnMake.Bind(wx.EVT_BUTTON, self.OnMake)

        self.mainSizer.Add(btnSizer, 0, wx.ALL|wx.CENTER, 5)
        self.mainSizer.Add(btnMake, 0, wx.ALL|wx.CENTER, 5)
        self.mainSizer.Add(self.bmp, 0, wx.ALL|wx.CENTER, 5)
        self.SetSizer(self.mainSizer)

        self.CreateStatusBar() # A StatusBar in the bottom of the window

        # Setting up the menu.
        filemenu= wx.Menu()

        # wx.ID_ABOUT and wx.ID_EXIT are standard ids provided by wxWidgets.
        menuOpen = filemenu.Append(wx.ID_OPEN, "Open", "Open a picture.")
        menuAbout = filemenu.Append(wx.ID_ABOUT, "&About"," Information about this program")
        menuExit = filemenu.Append(wx.ID_EXIT,"E&xit"," Terminate the program")

        # Creating the menubar.
        menuBar = wx.MenuBar()
        menuBar.Append(filemenu,"&File") # Adding the "filemenu" to the MenuBar
        self.SetMenuBar(menuBar)  # Adding the MenuBar to the Frame content.

        # Set events.
        self.Bind(wx.EVT_MENU, self.OnAbout, menuAbout)
        self.Bind(wx.EVT_MENU, self.OnExit, menuExit)
        self.Bind(wx.EVT_MENU, self.OnOpen, menuOpen)

        self.Show(True)

    def OnOpen(self,e):
        self.dirname = ''
        dlg = wx.FileDialog(self, "Choose a file", self.dirname, "", "*.png", wx.FD_OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename()
            self.dirname = dlg.GetDirectory()
            self.Destroy()
            self.Frame = ImgFrame(wx.Image('../Images/' + self.filename, wx.BITMAP_TYPE_PNG))
        dlg.Destroy()

    def OnAbout(self,e):
        # A message dialog box with an OK button. wx.OK is a standard ID in wxWidgets.
        dlg = wx.MessageDialog( self, "A small text editor", "About Sample Editor", wx.OK)
        dlg.ShowModal() # Show it
        dlg.Destroy() # finally destroy it when finished.

    def OnExit(self,e):
        self.Close(True)  # Close the frame.

    def OnViewEdges(self,e):
        hImg = wx.Image(self.hough, wx.BITMAP_TYPE_PNG)
        temp = hImg.ConvertToBitmap()
        self.bmp.SetBitmap(temp)

    def OnViewMask(self,e):
        mImg = wx.Image(self.mask, wx.BITMAP_TYPE_PNG)
        temp = mImg.ConvertToBitmap()
        self.bmp.SetBitmap(temp)

    def OnViewPath(self,e):
        pass

    def OnViewOriginal(self,e):
        self.bmp.SetBitmap(self.original)

    def OnMake(self,e):
        contours = CalculateContours(self.mask)

        with open("code.txt", 'w') as outfile:
            for contour in contours:
                print("ANAL")
                outfile.write(CalculateBroCodeFromContour(contour, 10))


class App(wx.App):
    def OnInit(self):
        self.Frame = StartFrame(None, "Test editor")
        self.Frame.Show()
        self.SetTopWindow(self.Frame)
        return True

def main():
    app = App()
    app.MainLoop()

if __name__ == '__main__':
           main()
