// Thsi code works, I try to learn QT

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QList>
#include <QVBoxLayout>
#include <QWidget>

class Shape {
public:
    Shape(const QString& type, const QString& color, const QRect& rect) : type(type), color(color), rect(rect) {}
    QString type;
    QString color;
    QRect rect;
};

class DrawingWidget : public QWidget {
public:
    DrawingWidget(QWidget* parent = nullptr) : QWidget(parent) {}

    void addShape(const QString& type, const QString& color, const QRect& rect) {
        shapes.append(Shape(type, color, rect));
        update();
    }

protected:
protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        for (const Shape& shape : shapes) {
            QColor color(shape.color);
            painter.setBrush(QBrush(color));
            if (shape.type == "rectangle") {
                painter.drawRect(shape.rect);
            }
        }
    }


private:
    QList<Shape> shapes;
};

class Controller : public QWidget {
    Q_OBJECT
public:
    Controller() {
        setWindowTitle("Shape Drawer");
        setGeometry(100, 100, 800, 600);

        drawingWidget = new DrawingWidget(this);

        inputShapeType = new QLineEdit(this);
        inputColor = new QLineEdit(this);
        inputCoordinates = new QLineEdit(this);
        addButton = new QPushButton("Add Shape", this);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(drawingWidget);
        layout->addWidget(inputShapeType);
        layout->addWidget(inputColor);
        layout->addWidget(inputCoordinates);
        layout->addWidget(addButton);
        setLayout(layout);

        connect(addButton, &QPushButton::clicked, this, &Controller::addShape);
    }

public slots:
    void addShape() {
        QString shapeType = inputShapeType->text();
        QString color = inputColor->text();
        QString coordinates = inputCoordinates->text();

        QStringList coordsList = coordinates.split(" ");
        if (coordsList.size() == 4) {
            int x = coordsList[0].toInt();
            int y = coordsList[1].toInt();
            int width = coordsList[2].toInt();
            int height = coordsList[3].toInt();

            drawingWidget->addShape(shapeType, color, QRect(x, y, width, height));
        }
        else {
            qDebug() << "Invalid coordinates format.";
        }
    }

private:
    DrawingWidget* drawingWidget;
    QLineEdit* inputShapeType;
    QLineEdit* inputColor;
    QLineEdit* inputCoordinates;
    QPushButton* addButton;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Controller controller;
    controller.show();

    return app.exec();
}

#include "main.moc"
