# Arduino-CnUtils
For Arduino -- Some of my own utilities and nice-to-have functions.  :)

If you have suggestions, and want to fork the repo or send pull requests, please do!

# Downloading
When you download, you'll get a file "Arduino-CnUtils-master.zip".  Extract to your ${HOME}/Arduino/libraries/ folder, and rename  "Arduino-CnUtils-Master" to "CnUtils".  Now start the IDE , go to `File > Sketchbook > libraries` to add CnUtils.  Once added, you can access the example sketch.

# Using Library In Your Application
There is an oddity about the Arduino IDE: a library cannot depend on another library.  In this case other libraries want to include `CnUtils.h` However, when compiling the EeValues library, `Arduino/libraries` isn't added to the *System Include Folder List*.  See [Arduino Build Process](https://code.google.com/p/arduino/wiki/BuildProcess) for details.  So your library, you need to do this:
`#include "../CnUtils/CnUtils.h"`


# This Library Depends On...
This library is stand-alone.

# License
Public Domain.


Have a nice day.

