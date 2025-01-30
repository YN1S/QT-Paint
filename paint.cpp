#include "paint.h"
#include "shapes/default_shape.h"


Paint::Paint(QFrame *parent)
{
    setObjectName("paint");
    setFocusPolicy(Qt::WheelFocus);
}

void Paint::setStrategy(std::unique_ptr<ActionStrategy> strategy)
{
    _strategy = std::move(strategy);
}

void Paint::addShape(std::unique_ptr<DefaultShape> shape)
{
    _shapes.push_back(std::move(shape));
}

void Paint::addConnection(ConnectionLine connection)
{
    _connections.append(connection);
}

void Paint::removeShape(DefaultShape *shapeToRemove)
{
    auto it = std::find_if(_shapes.begin(), _shapes.end(),
        [shapeToRemove](const std::unique_ptr<DefaultShape>& shape) {
            return shape.get() == shapeToRemove;
        });

    if (it != _shapes.end()) {_shapes.erase(it);}
}

void Paint::removeConnection(DefaultShape *shapeWithBounds)
{
    _connections.erase(std::remove_if(_connections.begin(), _connections.end(),
        [shapeWithBounds](const ConnectionLine& connection) {
            return connection.start == shapeWithBounds->center() || connection.end == shapeWithBounds->center();
        }), _connections.end());
}

void Paint::moveConnection(DefaultShape* shapeWithBounds, QPointF delta)
{
    for (ConnectionLine& connection : _connections) {
            if (connection.start == shapeWithBounds->center() - delta) {
                connection.start += delta;
            }
            if (connection.end == shapeWithBounds->center() - delta) {
                connection.end += delta;
            }
        }
}

const std::vector<std::unique_ptr<DefaultShape> > &Paint::shapes() const
{
    return _shapes;
}

const QList<ConnectionLine>& Paint::connections() const
{
    return _connections;
}

void Paint::loadFromFile(QFile &file)
{
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    // Чтение содержимого файла в QJsonDocument
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось разобрать JSON.");
        return;
    }

    QJsonObject rootObject = doc.object();
    QJsonArray shapesArray = rootObject["shapes"].toArray();
    QJsonArray connectionsArray = rootObject["connections"].toArray();

    // Очистка текущих данных
    _shapes.clear();
    _connections.clear();

    // Загрузка фигур из JSON с использованием fromJson
    for (const QJsonValue &shapeValue : shapesArray) {
        QJsonObject shapeObject = shapeValue.toObject();
        
        // Используем fromJson для создания фигуры
        std::unique_ptr<DefaultShape> shape = DefaultShape::fromJson(shapeObject);
        if (shape) {
            _shapes.push_back(std::move(shape));
        }
    }

    // Загрузка соединений из JSON
    for (const QJsonValue &connectionValue : connectionsArray) {
        QJsonObject connectionObject = connectionValue.toObject();

        QPointF start(connectionObject["startX"].toDouble(), connectionObject["startY"].toDouble());
        QPointF end(connectionObject["endX"].toDouble(), connectionObject["endY"].toDouble());

        _connections.append({start, end});
    }

    file.close();
}

void Paint::saveToFile(QFile &file) const
{
    QJsonArray shapesArray;

    for(const auto& shapePtr : _shapes)
    {
        shapesArray.append(shapePtr->toJson());
    }
    

    QJsonArray connectionsArray;
    for (const auto& connection : _connections) {
        QJsonObject connectionObject;
        connectionObject["startX"] = connection.start.x();
        connectionObject["startY"] = connection.start.y();
        connectionObject["endX"] = connection.end.x();
        connectionObject["endY"] = connection.end.y();
        connectionsArray.append(connectionObject);
    }
    
    QJsonObject rootObject;
    rootObject["shapes"] = shapesArray;
    rootObject["connections"] = connectionsArray;

    QJsonDocument doc(rootObject);

    if (!file.open(QIODevice::WriteOnly)) {
        // QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    file.write(doc.toJson());
    file.close();
}

void Paint::mousePressEvent(QMouseEvent *event)
{
    if (_strategy) {_strategy->mousePressEvent(event);}
}

void Paint::mouseMoveEvent(QMouseEvent *event)
{
    if (_strategy) _strategy->mouseMoveEvent(event);
}

void Paint::mouseReleaseEvent(QMouseEvent *event)
{
    if (_strategy) _strategy->mouseReleaseEvent(event);
}

void Paint::keyPressEvent(QKeyEvent *event)
{
    if (_strategy) _strategy->keyPressEvent(event);
}

void Paint::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    painter.setPen(Qt::black);

    for (auto& DefaultShape: _shapes)
    {
        DefaultShape->draw(&painter);
    }

    painter.setPen(Qt::black);
    for (const auto& [x, y] : _connections) {
        painter.drawLine(x, y);
    }
    


    if (_strategy)
    {
        _strategy->drawTemporary(&painter);
    }
}
