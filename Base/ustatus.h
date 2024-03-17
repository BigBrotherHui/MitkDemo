/**
 * @file    ustatus.h
 * @brief    内部系统全局静态变量.
 * @author    cc
 * @version    1.0
 * @date    2021-08-20
 *
 * # update （更新日志）
 *
 * [2021-08-20] <cc> v1.0
 *
 * + v1.0版发布.
 *
 */
#pragma execution_character_set("utf-8")
#ifndef USTATUS_H
#define USTATUS_H

#include <QString>
#include <QStackedWidget>
#include <QAction>
#include <QToolBar>
#include "vtkDICOMReader.h"
#include "vtkTransform.h"
#include "vtkSmartPointer.h"
#include "mainwindow.h"
#include "mitkStandaloneDataStorage.h"
class QmitkStdMultiWidget;
class QmitkLevelWindowWidget;
class THADicomSeries;
class DicomTag;
class QmitkMeasurementView;
class QmitkSegView;
class uFunBase;
class SqlDemo;
class Patient;
class StdMultiWidget;
class QTableWidgetItem;
class CaseManageControl;
class uStatus
{
public:


    uStatus::uStatus()
    {

    }
    static MainWindow *mMain;

	static QString mVer;
	static QString mKernelVer;
    static QString mMainWindow;
    static QString mMainToolbarWidget;
    static QString mMainFootbarWidget;
    static QString mMainCenterWidget;
    static QString mMainControlWidgetRight;
    static QString mMainControlWidgetLeft;
    static QMessageLogContext context;
    //Mian

	/**
	* @brief 系统统一路径
	*
	* emerg 描述。
	* @param[in]
	* @return
	* @see 
	* @note 系统运行路径
	* @since 2021-08-20
	* @exception
	* @deprecated
	*/
    static QString mMainDataDir;

    static QString mLogDir;
    static QString mBackupDir;
    static QString mDicomTmpDir;
	/**
	* @brief 程序运行时的主要配置文件信息
	*
	*/
	static QString mMainConfigureFileName;

	/**
	* @brief 当前病人档案中的病人信息
	*
	*/
    static QString mCurrentPatientID;

	/**
	* @brief 程序运行时的目录
	*
	*/
	static QString mMainPath;

	/**
	* @brief 在Data目录下存放Dicom文件的子目录的名称
	*
	*/
	static QString mDicomSubDir;

	/**
	* @brief 在Data目录下存放原始Dicom文件的子目录的名称
	*
	*/
	static QString mDicomOrgDir;

	/**
	* @brief 导出BMP
	*
	*/
	static QString mBMPSubDir;
	/**
	* @brief 在Data目录下存放配置文件的子目录的名称
	*
	*/
	static QString mParameterSubDir;
	/**
	* @brief 外部可执行生成文件目录
	*
	*/
	static QString mExternalGenDir;

    static mitk::DataStorage::Pointer mDataStorage;

    static QmitkStdMultiWidget *mMultiWidget;

    static SqlDemo *mSql;

	static int mUserLevel;

	static QString mUserCode;

	//static QString mCurClassName;
	//static QString mCurClassID;
    //DICOM
    static THADicomSeries* m_uDicomSeries;
    static vtkStringArray* mDicomSeriesFiles;
    static vtkDICOMReader* mDICOMReader;
    static DicomTag* mDicomTag ;
    static int mExtent[6];
    static double mOrigin[3];
    static double mSpacing[3];
    static double mCenter[3];
    static int Dims[3];
    static int mWW;
    static int mWL;
    static int mDefaultWW;
    static int mDefaultWL;


	//MainSeries
	/**
	* @brief 使用主图像序列目录名称
	*
	*/
	static QString mImageObjectPathName;

};

#endif // USTATUS_H
