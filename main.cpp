#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QPointer>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QFontDatabase>
#include <QMessageBox>
#include <vtkAutoInit.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkObject.h>
#include <vtkOutputWindow.h>
#include <itkOutputWindow.h>
#include "vtkOutputWindow.h"
#include "uStatus.h"
#include "ufunmap.h"
#include "ufunbaseinit.h"
#include "SqlDemo.h"
#include "mainframe.h"
//#include "runtimeutil.h"
#include <QMessageBox>

//For QT
#include <QtWidgets/QDesktopWidget>
#include <QSurfaceFormat>
#include <QtWidgets/QApplication>
#include <QtCore/QTranslator>
#include <QtWidgets/QSplashscreen>
#include <QStyleFactory> 
#include <QFile>
#include <QDir>
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTextCodec>
#include <QGLFormat>
#include <QSharedMemory>
//For VTK
#include <vtkAutoInit.h>
#include <vtkVersion.h>
#include <vtkMultiThreader.h>
#include <vtkOutputWindow.h>
#include <vtkOpenGLRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>


#include "Logger.h"
#include "Config.h"
//For CUDA
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
// mitk
#include <QmitkRegisterClasses.h>
#include <mitkRenderingManager.h>
#include <mitkStandaloneDataStorage.h>

#include "SystemControler.h"

// VTK_MODULE_INIT(vtkRenderingOpenGL2)
// VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
// VTK_MODULE_INIT(vtkInteractionStyle)
// VTK_MODULE_INIT(vtkRenderingFreeType)

//查找进程
bool FindProcess(const char * name)
{
    //  Mutex Object
    HANDLE hMutex  =  NULL;
    LPSTR lpszName  = LPSTR(name);

    hMutex  =  ::CreateMutex(NULL, FALSE, lpszName);
    DWORD dwRet  =  ::GetLastError();
    if  (ERROR_ALREADY_EXISTS  ==  dwRet)
    {
        CloseHandle(hMutex);
        return  true;
    }
    return false;
}

void checkVtkVersion()
{
#ifdef VTK_VERSION_NUMBER
	Logger::writeInfoLog("checkVtkVersion()", std::string("Source version: " + std::string(vtkVersion::GetVTKSourceVersion())).c_str());
	Logger::writeInfoLog("checkVtkVersion()", std::string("Major Version: " + std::to_string(vtkVersion::GetVTKMajorVersion())).c_str());
	Logger::writeInfoLog("checkVtkVersion()", std::string("Minor version: " + std::to_string(vtkVersion::GetVTKMinorVersion())).c_str());
#elif VTK_VERSION_NUMBER_NOT_DEFINED
	Logger::writeInfoLog("checkVtkVersion()", std::string("VTK VTK_VERSION_NUMBER is not defined. ");)
#endif
}

void checkCudaVersion()
{
	int deviceCount = 0;
	cudaError_t ret = ::cudaGetDeviceCount(&deviceCount);
	if (ret != cudaError::cudaSuccess) {
		Logger::writeInfoLog("checkCudaVersion()", (std::string("Check cuda device fail, error_code = ") + std::to_string(ret)).c_str());
		return;
	}

	for (int dev = 0; dev < deviceCount; dev++)
	{
		int driver_version(0), runtime_version(0);
		cudaDeviceProp deviceProp;
		::cudaGetDeviceProperties(&deviceProp, dev);
		if (dev == 0)
			if (deviceProp.minor = 9999 && deviceProp.major == 9999)
				qDebug() << "\n";

		Logger::writeInfoLog("checkCudaVersion()", std::string("*** Device: " + std::to_string(dev) + " ," + std::string(deviceProp.name) + "***").c_str());

		::cudaDriverGetVersion(&driver_version);
		Logger::writeInfoLog("checkCudaVersion()", std::string("CUDA Drive Version: " + std::to_string(driver_version / 1000) + " , " + std::to_string((driver_version % 1000) / 10)).c_str());

		::cudaRuntimeGetVersion(&runtime_version);
		Logger::writeInfoLog( "checkCudaVersion()", std::string("CUDA Runtime Version: " + std::to_string(runtime_version / 1000) + " , " + std::to_string((runtime_version % 1000) / 10)).c_str());
		Logger::writeInfoLog( "checkCudaVersion()", std::string("Device computing capacity: " + std::to_string(deviceProp.major) + std::to_string(deviceProp.minor)).c_str());

		QByteArray temp;
		temp = QString("Total amount of Global Memory: %1").arg(deviceProp.totalGlobalMem).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Number of SMs: %1").arg(deviceProp.multiProcessorCount).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Total amount of Constant Memory: %1").arg(deviceProp.totalConstMem).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Total amount of Shared Memory per block: %1").arg(deviceProp.sharedMemPerBlock).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Total number of registers available per block: %1").arg(deviceProp.regsPerBlock).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Warp size: %1").arg(deviceProp.warpSize).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Maximum number of threads per SM: %1").arg(deviceProp.maxThreadsPerMultiProcessor).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Maximum number of threads per block: %1").arg(deviceProp.maxThreadsPerBlock).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Maximum size of each dimension of a block: %1, %2, %3").arg(deviceProp.maxThreadsDim[0]).arg(deviceProp.maxThreadsDim[1]).arg(deviceProp.maxThreadsDim[2]).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Maximum size of each dimension of a grid: %1, %2, %3").arg(deviceProp.maxGridSize[0]).arg(deviceProp.maxGridSize[1]).arg(deviceProp.maxGridSize[2]).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Maximum memory pitch: %1").arg(deviceProp.memPitch).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Texture alignment: %1").arg(deviceProp.texturePitchAlignment).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Clock rate: %1").arg(deviceProp.clockRate * 1e-6f).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Memory Clock rate: %1").arg(deviceProp.memoryClockRate * 1e-3f).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());

		temp = QString("Memory Bus Width: %1").arg(deviceProp.memoryBusWidth).toLatin1();
		Logger::writeInfoLog( "checkCudaVersion()", temp.data());
	}
}
void initVtk()
{
	vtkMultiThreader::SetGlobalMaximumNumberOfThreads(8);
	checkVtkVersion();

	// 设置window渲染方式
	vtkOutputWindow::SetGlobalWarningDisplay(0);
	vtkOpenGLRenderWindow::SetGlobalMaximumNumberOfMultiSamples(8);

	// needed to ensure appropriate OpenGL context is created for VTK rendering.
	//QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
	QGLFormat::setDefaultFormat(QGLFormat::defaultFormat());
}


#if _MSC_VER >= 1600
#pragma execution_character_set("UTF-8")
#endif
void setCodeForLocal()
{
	//设置中文编码
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
}
int main(int argc, char *argv[])
{
	//vtkOutputWindow::SetGlobalWarningDisplay(0);
    QApplication a(argc, argv);
    a.setApplicationName("DentalRobot");
    a.setOrganizationName("None");

    
	
    if(FindProcess("DentalRobot.exe"))
    {
        QMessageBox::warning(nullptr,QObject::tr("警告"),QObject::tr("请不要重复运行程序！"));
        return 0;
    }
//     if (Config::GetRunning())
//     {
//         QMessageBox::warning(nullptr, QObject::tr("警告"), QObject::tr("上一次程序运行出现异常结束，请联系供应商！"));
// 		Config::SetRunning(false);
//     }
    QmitkRegisterClasses();
    RCF::init();
	//For CUDA
	checkCudaVersion();

	setCodeForLocal();
	//For VTK
	initVtk();
	Config::init(/*QDir::currentPath() + */"../DentalRobot/settings.ini");
    //
    uFunMap::mFunBaseMap = new QMap<QString, QPointer<uFunBase> >();
    uStatus::mDataStorage = mitk::StandaloneDataStorage::New();

    //
    uStatus::mMainDataDir = QCoreApplication::applicationDirPath() + "/data";
    uStatus::mMainPath = QCoreApplication::applicationDirPath();

    //
    uStatus::mSql=new SqlDemo();

    if(!uStatus::mSql->Initialize())
    {
        return 0;
    }
    MainFrame m;
	SystemControler::getInstance();
	//开启所有线程
	SystemControler::getInstance()->startThreads();
    m.showMaximized();
    return a.exec();
}
