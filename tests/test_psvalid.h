#ifndef TEST_PSVALID_H
#define TEST_PSVALID_H

#include <QObject>

class Test_PSValid : public QObject
{
    Q_OBJECT
public:
    Test_PSValid(QObject *parent = 0);

private slots:
    void variantTest();
    void createVariantFromHashCode();

    void createVariantFromName();

    void variantConvertTest();

    void variantEquals();

    void variantLess();

    void setGetTest();

    void variantIternalProperty();

    void variantCopy();

    void variantMapTest();
    void variantVectorTest();
};

#endif // TEST_PSVALID_H
