MULTIPLIER = 1

def WriteBroCodeMoveAbsolute(to_point):
    bro_code = "L({x},{y},{z});"
    return bro_code.format(x=int(to_point[0] * MULTIPLIER), y=int(to_point[1] * MULTIPLIER), z=int(to_point[2] * MULTIPLIER))

def WriteBroCodeMoveRelative(to_point):
    bro_code = "R({x},{y},{z});"
    return bro_code.format(x=int(to_point[0] * MULTIPLIER), y=int(to_point[1] * MULTIPLIER), z=int(to_point[2] * MULTIPLIER))

print(WriteBroCodeMove([1, 2, 3]))
