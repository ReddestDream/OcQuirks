import sys, os
finput = input if sys.version_info >= (3,0) else raw_input

os.chdir(os.path.dirname(os.path.realpath(__file__)))
target_file = os.path.join(os.getcwd(),"Platform","OcQuirks","OcQuirks.c")

def cls():
    os.system("cls" if os.name=="nt" else "clear")

def head(text = None, width = 55):
    if text == None:
        text = ""
    cls()
    print("  {}".format("#"*width))
    mid_len = int(round(width/2-len(text)/2)-2)
    middle = " #{}{}{}#".format(" "*mid_len, text, " "*((width - mid_len - len(text))-2))
    if len(middle) > width+1:
        # Get the difference
        di = len(middle) - width
        # Add the padding for the ...#
        di += 3
        # Trim the string
        middle = middle[:-di] + "...#"
    print(middle)
    print("#"*width)

def get_name_val(entry):
    entry = entry.strip().replace("\t"," ").replace("  "," ").replace("  "," ").lstrip(".").rstrip(";,")
    t = "bool"
    if entry.lower().startswith("int "):
        t = "int"
        entry = entry[4:]
    name = entry.split("=")[0].strip()
    val  = entry.split("=")[1].strip()
    # val = True if val.lower() in ("true","1") else False
    return (name,val,t)

def get_val(val):
    return True if val.lower() in ("true","1") else False

def main():
    # Let's load the target file and show the options
    if not os.path.exists(target_file):
        head("WARNING")
        print("")
        print("{} was not found!".format(target_file))
        print("")
        exit(1)
    with open(target_file,"r") as f:
        source = f.read()
    # Let's gather our settings.  We're looking for lines that when stripped start with int or .
    settings = []
    for line in source.split("\n"):
        linet = line.strip()
        if linet.startswith((".","int ")):
            settings.append({"original":line,"edited":line})
    if not len(settings):
        # Nothing found
        head("WARNING")
        print("")
        print("No valid settings were found!")
        print("")
        exit(1)
    # Let's preset a formatted list
    while True:
        head("Current Settings")
        print("")
        for i,x in enumerate(settings):
            name,val,t = get_name_val(x["edited"])
            print("{}. {} = {}".format(i+1,name,get_val(val)))
            # Let's strip the ; or , ending and the "int " or "." header
        print("")
        print("S. Save")
        print("Q. Quit")
        print("")
        menu = finput("Please choose a setting to toggle:  ")
        if menu.lower() == "q":
            exit()
        if menu.lower() == "s":
            # We savin!
            new_out = source
            for s in settings:
                new_out = new_out.replace(s["original"],s["edited"])
            with open(target_file,"w") as f:
                f.write(new_out)
            print("")
            print("Saved to {}".format(target_file))
            print("")
            print("Done.")
            print("")
            exit()
        try:
            menu = int(menu)
        except:
            continue
        if menu < 1 or menu > len(settings):
            continue
        current = settings[menu-1]
        name,val,t = get_name_val(current["edited"])
        # Let's toggle it and re-add to the settings list
        if t.lower() == "int":
            nval = "0" if val == "1" else "1"
        else:
            nval = "TRUE" if val.lower() == "false" else "FALSE"
        current["edited"] = current["edited"].replace(val,nval)
main()