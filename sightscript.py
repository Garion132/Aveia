
# Runs through the prov histories and duplicates discovered_by = TECH_GROUP_1, adding discovered_by = TECH_GROUP_2 to the file under it. 
# This is so Garion doesn't have to break his fingers.
# 
# Coded by Strat.


#Which to be TECH_GROUP_1 and TECH_GROUP_2
TECH_GROUP_1 = "lake_elves_group"
TECH_GROUP_2 = "ork_group"



from os import getcwd
from os import listdir
from os.path import isfile, join

# Get the files
mypath = getcwd() + "\\history\\provinces\\"
files = [ f for f in listdir(mypath) if isfile(join(mypath, f))]

# Magic
for f in files:
    with open(mypath + f, 'r+') as fd:
        contents = fd.readlines()
        if "discovered_by" in contents[-1] and TECH_GROUP_1 in contents[-1]:  # Handle last line to prevent IndexError
            contents.append("\ndiscovered_by = " + TECH_GROUP_2)
        else:
            for index, line in enumerate(contents):
                if "discovered_by" in line and TECH_GROUP_1 in line and TECH_GROUP_2 not in contents[index + 1]:
                    contents.insert(index + 1, "discovered_by = " + TECH_GROUP_2 + "\n")
                    break
        fd.seek(0)
        fd.writelines(contents)