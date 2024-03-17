#pragma once
#include <QHash>
#include <QObject>
#include "ufunbase.h"
#include <QDebug>
class uReflect
{
public:
	static void registerAllClasses();
	template<typename T>
	static void registerClass() {
		constructors().insert(T::staticMetaObject.className(), &constructorHelper<T>);
	}

	static uFunBase* newInstance(const QString& className, QWidget* parent = nullptr) {
		Constructor constructor = constructors().value(className);
		if (constructor == nullptr)
			return nullptr;
		return (*constructor)(parent);
	}

private:
	typedef uFunBase* (*Constructor)(QWidget* parent);

	template<typename T>
	static uFunBase* constructorHelper(QWidget* parent) {
		return new T(parent);
	}

	static QHash<QString, Constructor>& constructors() {
		static QHash<QString, Constructor> instance;
		return instance;
	}
};