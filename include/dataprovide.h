#ifndef DATAPROVIDE_H
#define DATAPROVIDE_H

#include <QObject>
#include "windows.h"
#include <QSize>

static void* pt2Object = NULL; //对象指针

void WINAPI ProgressCallbackForRealTimePenDatas(int x, int y, int preasure);

typedef int(WINAPI *PopenPort)();

typedef int(WINAPI *PgetDGBleInfo)(char *, char *);

typedef int(WINAPI *PgetDGVersion)(char *);

typedef long(WINAPI *PsetDGBleName)(char *);

typedef int(WINAPI *PconnectDevice)();

typedef int(WINAPI *PgetDeviceBleInfo)(char *, char *);
typedef int(WINAPI *PgetDeviceName)(char *);
typedef int(WINAPI *PgetDeviceFirmwareVersion)(char *, char *);

typedef int(WINAPI *PgetDeviceBatteryState)(int, int);

typedef int(WINAPI *PsetDeviceDateTimeWithSecond)(int);

typedef int(WINAPI *PsetDeviceName)(char *);

typedef int(WINAPI *PhardwareReset)();

typedef int(WINAPI *PfactoryReset)();

typedef int(WINAPI *PswitchToRealTimeMode)();

typedef int(WINAPI *PswitchToUploadMode)();
typedef int(WINAPI *PqueryFileConut)(int &);

typedef int(WINAPI *PtransferOldestFile)();

typedef int(WINAPI *PtransferNewestFile)();

typedef int(WINAPI *PgetUploadFileInfo)(int &, int &);

typedef int(WINAPI *PstopTransfer)();

typedef int(WINAPI *PGetUploadFile)();

typedef int(WINAPI *PdeleteUploadFile)();

typedef int(WINAPI *PopenFileEncryptionWithKey)(char *);

typedef int(WINAPI *PcloseFileEncryptionByKey)(char *);
typedef int(WINAPI *PqueryFileEncryptionStatus)(int &);
typedef int(WINAPI *PverifyFileEncryptionByKey)(char *);

typedef  void(WINAPI *CallbackFun)(int x, int y, int preasure);
typedef  void(WINAPI *PSetCallBackForRealTimePenDatas)(CallbackFun callbackfun);


class DataCallback;
class DataProvide : public QObject
{
    Q_OBJECT

public:
    explicit DataProvide(QObject *parent = 0);
    ~DataProvide();
    void setDataCallback(DataCallback *pcall)
    {
        m_pDataCall = pcall;
    }
    void setData(int x, int y, int preasure);
    QSize getCanvasSize();

private:
    void loadLibrary();
private:
    DataCallback *m_pDataCall;
    PopenPort openPort ;

    PgetDGBleInfo getDGBleInfo ;

    PgetDGVersion getDGVersion ;

    PsetDGBleName  setDGBleName ;

    PconnectDevice connectDevice ;

    PgetDeviceBleInfo getDeviceBleInfo;

    PgetDeviceName getDeviceName;

    PgetDeviceFirmwareVersion getDeviceFirmwareVersion ;
    PgetDeviceBatteryState getDeviceBatteryState ;

    PsetDeviceDateTimeWithSecond setDeviceDateTimeWithSecond ;

    PsetDeviceName setDeviceName ;

    PhardwareReset hardwareReset ;

    PfactoryReset factoryReset;
    PswitchToRealTimeMode switchToRealTimeMode;

    PswitchToUploadMode switchToUploadMode;

    PqueryFileConut queryFileConut;

    PtransferOldestFile transferOldestFile;

    PtransferNewestFile transferNewestFile ;

    PgetUploadFileInfo getUploadFileInfo ;

    PstopTransfer stopTransfer ;

    PGetUploadFile GetUploadFile ;

    PdeleteUploadFile deleteUploadFile ;

    PopenFileEncryptionWithKey openFileEncryptionWithKey ;

    PcloseFileEncryptionByKey closeFileEncryptionByKey;

    PqueryFileEncryptionStatus queryFileEncryptionStatus;

    PverifyFileEncryptionByKey verifyFileEncryptionByKey;


    PSetCallBackForRealTimePenDatas SetCallBackForRealTimePenDatas;

    QSize mCanvasSize;
};

#endif // DATAPROVIDE_H
