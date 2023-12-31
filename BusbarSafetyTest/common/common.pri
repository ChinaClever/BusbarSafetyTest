
INCLUDEPATH += $$PWD

include(excel/excel.pri)
include(chars/chars.pri)
include(logcom/logcom.pri)
include(sqlcom/sqlcom.pri)
include(testcom/testcom.pri)
include(tablecom/tablecom.pri)
include(websocket/websocket.pri)
include(serialport/serialport.pri)

HEADERS += \	
    $$PWD/msgbox.h \
    $$PWD/common.h \
    $$PWD/configbase.h \
    $$PWD/sysconfigfile.h \
    $$PWD/datapacket.h
   
	
SOURCES += \	
    $$PWD/msgbox.cpp \
    $$PWD/common.cpp \
    $$PWD/configbase.cpp \
    $$PWD/sysconfigfile.cpp \
    $$PWD/datapacket.cpp
   

FORMS += \




