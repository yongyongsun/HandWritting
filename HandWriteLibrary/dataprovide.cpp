#include "dataprovide.h"
#include <QLibrary>
#include <QCoreApplication>
#include <qDebug>
#include "DataCallback.h"

void WINAPI ProgressCallbackForRealTimePenDatas(int x, int y, int preasure)
{
    if (pt2Object != NULL)
    {
        DataProvide* pb2 = static_cast<DataProvide*>(pt2Object);
        pb2->setData(x,y,preasure);
    }
}

DataProvide::DataProvide(QObject *parent) :
    QObject(parent)
  , m_pDataCall(NULL)
{
    mCanvasSize = QSize();
    pt2Object = (void*)this;
    loadLibrary();
}

DataProvide::~DataProvide()
{

}

void DataProvide::setData(int x, int y, int preasure)
{

    if (m_pDataCall != NULL)
    {
        m_pDataCall->dataActivated(x,y,preasure);
    }
}

QSize DataProvide::getCanvasSize()
{
    QSize size = QSize(21000,30000);
    return size;
}

void DataProvide::loadLibrary()
{
    QString str = QCoreApplication::applicationDirPath() + "/DigitNoteController.dll";
    qDebug()<<"librayr path = "<<str;
     QLibrary lib1(str);
     if (lib1.load())
     {
         qDebug() << "load ok!";
         openPort = (PopenPort) lib1.resolve("_openPort@0");
         getDGBleInfo = (PgetDGBleInfo)lib1.resolve("_getDGBleInfo");

         getDGVersion = (PgetDGVersion)lib1.resolve("_getDGVersion@4");

         setDGBleName = (PsetDGBleName)lib1.resolve("_setDGBleName@4");

         connectDevice = (PconnectDevice)lib1.resolve("_connectDevice@0");

         getDeviceBleInfo = (PgetDeviceBleInfo)lib1.resolve("_getDeviceBleInfo@8");

         getDeviceName = (PgetDeviceName)lib1.resolve("_getDeviceName@4");

         getDeviceFirmwareVersion = (PgetDeviceFirmwareVersion)lib1.resolve("_getDeviceFirmwareVersion@8");
         getDeviceBatteryState = (PgetDeviceBatteryState)lib1.resolve("_getDeviceBatteryState@8");

         setDeviceDateTimeWithSecond = (PsetDeviceDateTimeWithSecond)lib1.resolve( "_getDeviceDataTimeWithSecond@4");

         setDeviceName = (PsetDeviceName)lib1.resolve("_setDeviceName@4");

         hardwareReset = (PhardwareReset)lib1.resolve("_hardwareReset@0");

         factoryReset = (PfactoryReset)lib1.resolve("_factoryReset@0");
         switchToRealTimeMode = (PswitchToRealTimeMode)lib1.resolve("_switchToRealTimeMode@0");
         switchToUploadMode = (PswitchToUploadMode)lib1.resolve("_switchToUploadMode@0");

         queryFileConut = (PqueryFileConut)lib1.resolve("_queryFileConut@4");

         transferOldestFile = (PtransferOldestFile)lib1.resolve("_transferOldestFile@0");

         transferNewestFile = (PtransferNewestFile)lib1.resolve("_transferNewestFile@0");

         getUploadFileInfo = (PgetUploadFileInfo)lib1.resolve("_getUploadFileInfo@8");

         stopTransfer = (PstopTransfer)lib1.resolve("_stopTransfer@0");

         GetUploadFile = (PGetUploadFile)lib1.resolve("_GetUploadFile@0");

         deleteUploadFile = (PdeleteUploadFile)lib1.resolve("_deleteUploadFile@0");

         openFileEncryptionWithKey = (PopenFileEncryptionWithKey)lib1.resolve("_openFileEncryptionWithKey@4");

         closeFileEncryptionByKey = (PcloseFileEncryptionByKey)lib1.resolve("_closeFileEncryptionByKey@4");

         queryFileEncryptionStatus = (PqueryFileEncryptionStatus)lib1.resolve("_queryFileEncryptionStatus@4");

         verifyFileEncryptionByKey = (PverifyFileEncryptionByKey)lib1.resolve("_verifyFileEncryptionByKey@4");

         SetCallBackForRealTimePenDatas = (PSetCallBackForRealTimePenDatas)lib1.resolve("_SetCallBackForRealTimePenDatas@4");

         if (openPort != NULL)
         {
             int Ret = openPort();
             if (Ret == 0)
             {
                 //openPort Success
                 if (switchToRealTimeMode != NULL)
                 {
                     int Ret = switchToRealTimeMode();
                     if (Ret == 0)
                     {
                         SetCallBackForRealTimePenDatas((CallbackFun)ProgressCallbackForRealTimePenDatas);
                     }
                 }
             }
         }


     } else
     {
         QString ss = lib1.errorString();
         qDebug() << "[error]load error!"<<ss;
     }
}
