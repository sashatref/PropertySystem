#include "../project_pch.h"
#include "functions.h"

namespace Text
{

QString getDateFormatString()
{
    return "dd.MM.yyyy";
}

QString getDateTimeFormatString()
{
    return "dd.MM.yyyy hh:mm:ss";
}

bool writeToFile(const QString &_path, const QString &_text, bool _append, const QString &_codec)
{
    QFile file(_path);
    if(file.open(_append ? QIODevice::Append : QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(qPrintable(_codec));
        stream << _text;
        file.close();
        return true;
    }

    return false;
}

QString readFromFile(const QString &_path, const QString &_codec)
{
    QString result;

    QFile file(_path);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(_codec.toStdString().c_str());
        result = stream.readAll();
        file.close();
    }

    return result;
}

QString textWithDateTimeStamp(const QString &_text)
{
    return QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " | " + _text;
}

QString textWithTimeStamp(const QString &_text)
{
    return QTime::currentTime().toString("hh:mm:ss") + " | " + _text;
}

QString getRandomString(int _minLenght, int _maxLenght)
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    if(_minLenght > _maxLenght)
    {
        _minLenght = _maxLenght;
    }

    int randomStringLength;
    if(_minLenght == _maxLenght)
    {
        randomStringLength = _minLenght;
    } else
    {
        randomStringLength = _minLenght + (rand() % (_maxLenght - _minLenght + 1));
    }

    QString randomString;
    for(int i=0; i < randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

QDate getRandomDate()
{
    return QDate(1980 + rand() % 50, rand() % 12, rand() % 30);
}

QDateTime getRandomeDateTime()
{
    return QDateTime(getRandomDate(), getRandomTime());
}

QTime getRandomTime()
{
    return QTime(rand() %24, rand() % 60, rand() % 60);
}



QString getHourEnding(int _value)
{
    QString hourEndings[] = {"", "а", "ов"};
    return QString("час%1").arg(hourEndings[GetDigitEnding(_value)]);
}

QString getSecondEnding(int _value)
{
    QString secondEndings[] = {"а", "ы", ""};
    return QString("секунд%1").arg(secondEndings[GetDigitEnding(_value)]);
}

QString getMinuteEnding(int _value)
{
    QString minuteEndings[] = {"а", "ы", ""};
    return QString("минут%1").arg(minuteEndings[GetDigitEnding(_value)]);
}

DigitEnding GetDigitEnding(const int iValue) /* Определение склонения числа */
{
    int n = iValue % 100;

    DigitEnding r = de10;

    if (n > 4 && n < 20)
        return r;

    n = n % 10;
    if (n == 1)
        r = de1;
    else if (n > 1 && n < 5)
        r = de4;

    return r;
}



QString getShortFilePath(const QString &fullPath, int _maxSize /*= 40*/)
{
    QString tempPath = fullPath;
    tempPath.replace("/", "\\");

    //если строка нормально влазит в лимит
    if(fullPath.size() <= _maxSize)
    {
        return tempPath;
    }

    //если строка это вовсе не путь
    if(tempPath.indexOf("\\") == -1)
    {
        return getShortText(tempPath, _maxSize);
    }

    QStringList items = tempPath.split("\\");

    if(items.size() > 1)
    {
        QString first = items.first();
        QString last = items.last();
        if(last.size() > _maxSize - first.size())
        {
            QString shortLast = getShortText(last, _maxSize - first.size() - 5);
            return QString("%1\\...\\%2").arg(items.first()).arg(shortLast);
        }
    }

    int index = 0;
    int totalLenght = 0;

    for(int i = items.size() - 1 ; i > -1; i--)
    {
        totalLenght += items.at(i).size();
        if(totalLenght < _maxSize - items.first().size() - 4)
        {
            index++;
        } else
        {
            break;
        }
    }

    QStringList subArr = items.mid(items.size() - index);
    QString result = QString("%1\\...\\%2").arg(items.first()).arg(subArr.join("\\"));

    return result;
}

QString getShortText(const QString &_text, int _size)
{
    if(_text.size() <= _size)
    {
        return _text;
    }

    int mid = (_size - 3) / 2;
    int ostacha = (_size - 3) % 2;

    return QString("%1...%2").arg(_text.left(mid)).arg(_text.mid(_text.size() - mid - ostacha));
}

QString getTextWithSymbolAround(const QString &_text, int _totalLenght, const QString &_symbol)
{
    if(_totalLenght <= _text.length()) return _text;

    QString result;

    int whiteCount = _totalLenght - _text.length();

    addChars(result, _symbol, whiteCount / 2);
    result += _text;
    addChars(result, _symbol, whiteCount / 2);

    if(whiteCount % 2 != 0)
    {
        addChars(result, _symbol, 1);
    }

    return result;
}

QString &addChars(QString &_text, const QString &_char, int _lenght)
{
    for(int i = 0 ; i < _lenght; i++)
    {
        _text.append(_char);
    }

    return _text;
}

int idFromString(const QString &_valueToParse)
{
    int index1 = _valueToParse.lastIndexOf("(");
    int index2 = _valueToParse.lastIndexOf(")");
    if(index1 == -1 || index2 == -1)
    {
        return -1;
    }

    return _valueToParse.mid(index1 + 1, index2 - index1 - 1).toInt();
}

QString enumToString(int _value, const QMetaEnum &_metaEnum, const QMap<QString, QString> &_namesMap)
{
    QString keyValue = _metaEnum.valueToKey(_value);
    if(_namesMap.contains(keyValue))
    {
        keyValue = _namesMap[keyValue];
    }

    return keyValue;
}

QStringList flagsToString(int _value, const QMetaEnum &_metaEnum, const QMap<QString, QString> &_namesMap)
{
    QStringList listValues;

    for(int i = 0 ; i < _metaEnum.keyCount(); i++)
    {
        int bitMask = _metaEnum.value(i);
        QString name = _metaEnum.key(i);

        if(bitMask == 0 && _value != 0) continue;

        if(_namesMap.contains(name))
        {
            name = _namesMap[name];
        }

        bool testBit = ((_value & bitMask) == bitMask);

        if(testBit)
        {
            listValues << name;
        }
    }

    return listValues;
}

QString getTimeFormatted(int _hour, int _min, int _sec, bool hideNullElements)
{
    QString text;

    bool prevPresent = false;
    if(_hour || !hideNullElements)
    {
        text += QString("%1 %2").arg(_hour).arg(QObject::tr("ч", "часов"));
        prevPresent = true;
    }

    if(_min || !hideNullElements)
    {
        if(prevPresent) text += " ";
        text += QString("%1 %2").arg(_min).arg(QObject::tr("м", "минут"));
        prevPresent = true;
    }

    if(prevPresent) text += " ";
    text += QString("%1 %2").arg(_sec).arg(QObject::tr("с", "секунд"));

    return text;
}

QString enumToString(int _value,
                     const QMetaObject *_mo,
                     const QString &_enumName,
                     const QMap<QString, QString> &_namesMap)
{
    for(int i = _mo->enumeratorOffset(); i < _mo->enumeratorCount(); i++)
    {
        if(_mo->enumerator(i).name() == _enumName)
        {
            return enumToString(_value, _mo->enumerator(i), _namesMap);
        }
    }

    return QString();
}

QVariantMap parseJson(const QByteArray &_jsonData)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(_jsonData, &error);
    return document.object().toVariantMap();
}

QByteArray writeToJson(const QVariantMap &_map)
{
    return QJsonDocument(QJsonObject::fromVariantMap(_map)).toJson();
}

QStringList unionList(const QStringList &_list1, const QStringList &_list2, Qt::CaseSensitivity _sensivity)
{
    QStringList res;

    for (int i = 0, count = _list1.size(); i < count; ++i)
    {
        if(_list2.contains(_list1[i], _sensivity))
        {
            res << _list1[i];
        }
    }

    return res;
}



}


void Translate::installTranslator(const QString &_path, const QString &_prefix, QList<QTranslator *> &_translatorList, QObject *parent)
{
    //удаляем утсновленные ранее трансляторы
    for(int i = 0 ; i < _translatorList.size(); i++)
    {
        delete _translatorList[i];
    }
    _translatorList.clear();

    //загружаем новые и добавляем их в список
    QDir trDir(_path);
    if(trDir.exists())
    {
        QStringList files = trDir.entryList(QStringList() << _prefix + "*.qm");

        for(int i = 0 ; i < files.size(); i++)
        {
            QTranslator *translator = new QTranslator(parent);
            translator->load(files[i], _path);
            qApp->installTranslator(translator);
            _translatorList.append(translator);
        }
    }
}

QString getCommandLine()
{    
    return qApp->arguments().join(" ");
}


QStringList Files::countDir(const QString &_path, const QStringList &_ext, bool *_stop)
{
    QStringList files;
    if(_stop && *_stop) ///<остановка процесса поиска каталогов
    {
        return files;
    }

    QDir dir(_path);

    QStringList entryListFiles = dir.entryList(_ext, QDir::Files);
    QStringList entryListDirs = dir.entryList(QDir::Dirs);

    for(int i = 0 ; i < entryListFiles.size(); i++)
    {
        files.append(_path + "/" + entryListFiles[i]);
    }

    for(int i = 0; i < entryListDirs.size(); i++)
    {
        if(entryListDirs[i] != "." && entryListDirs[i] != "..")
        {
            files.append(countDir(_path + "/" + entryListDirs[i], _ext, _stop));
        }
    }

    return files;
}

void Files::createDirForFile(const QString &_filePath)
{
    QString filePath = _filePath;
    filePath.replace("\\", "/");
    if(filePath.contains("/"))
    {
        QString dir = filePath.left(filePath.lastIndexOf("/"));
        QDir().mkpath(dir);
    }
}

QString Files::calcHash(const QByteArray &_bData)
{
    return QString(QCryptographicHash::hash(_bData, QCryptographicHash::Md5).toHex());
}

void SaveLoad::saveToByteArray(QByteArray &_data, const QVariantMap &_map)
{
    QDataStream stream(&_data, QIODevice::WriteOnly);
    stream << _map;
}

void SaveLoad::loadFromByteArray(QByteArray &_data, QVariantMap &_map)
{
    QDataStream stream(&_data, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_5);
    stream >> _map;
}

QString Files::calcHash(const QDir &_filePath, int _firstBytes)
{
    QCryptographicHash cryp(QCryptographicHash::Md5);
    QFile file(_filePath.path());
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray all;
        while (!file.atEnd())
        {
            QByteArray line = file.read(1024);
            cryp.addData(line);
            all+=line;

            if(_firstBytes != -1 && line.size() < 1024)
            {
                break;
            }
        }
    }
    return cryp.result().toHex().data();
}




namespace Numerics
{
double getRandomeDouble(int max)
{
    return rand() % max + (double)(rand() % 100) / (double)100;
}

int &fixValue(int &_value, int _min, int _max)
{
    if(_value > _max)
    {
        _value = _max;
    } else if(_value < _min)
    {
        _value = _min;
    }

    return _value;
}

}

void Files::unZip(const QString &_zipfilename, const QString &_filename)
{
    QFile infile(_zipfilename);
    QFile outfile(_filename);
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);
    QByteArray uncompressedData = infile.readAll();
    QByteArray compressedData = qUncompress(uncompressedData);
    outfile.write(compressedData);
    infile.close();
    outfile.close();
}

void Files::zip(const QString &_filename, const QString &_zipfilename)
{
    QFile infile(_filename);
    QFile outfile(_zipfilename);
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);
    QByteArray uncompressedData = infile.readAll();
    QByteArray compressedData = qCompress(uncompressedData,9);
    outfile.write(compressedData);
    infile.close();
    outfile.close();
}

bool SaveLoad::saveLayout(const QDir &_path, QMainWindow *_mainWindow)
{
    QString mypath = _path.path();

    mypath.replace("\\", "/");
    if(mypath.contains("/"))
    {
        QString dir = mypath.left(mypath.lastIndexOf("/"));
        QDir().mkpath(dir);
    }

    QFile file(_path.path());
    if (!file.open(QFile::WriteOnly))
    {
        return false;
    }

    QByteArray geo_data = _mainWindow->saveGeometry();
    QByteArray layout_data = _mainWindow->saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        return false;
    }
    return true;
}

bool SaveLoad::loadLayout(const QDir &_path, QMainWindow *_mainWindow)
{
    QFile file(_path.path());
    if (!file.open(QFile::ReadOnly))
    {
        return false;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = _mainWindow->restoreGeometry(geo_data);
    if (ok)
        ok = _mainWindow->restoreState(layout_data);

    if (!ok) {
        return false;
    }
    return true;
}

QByteArray SaveLoad::saveLayout(QMainWindow *_mainWindow)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << _mainWindow->saveGeometry();
    stream << _mainWindow->saveState();

    return data;
}

void SaveLoad::loadLayout(const QByteArray &_data, QMainWindow *_mainWindow)
{
    QByteArray data = _data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    QByteArray geo_data;
    QByteArray layout_data;

    stream >> geo_data;
    stream >> layout_data;

    _mainWindow->restoreGeometry(geo_data);
    _mainWindow->restoreState(layout_data);
}
