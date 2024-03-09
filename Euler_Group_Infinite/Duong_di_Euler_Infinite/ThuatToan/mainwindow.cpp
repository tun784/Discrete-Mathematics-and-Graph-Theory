// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsLineItem>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <QSet>
#include <QStack>
#include <QVector>
#include <QTextEdit>
#include <QMap>
#include <limits>

using namespace std;

//Lập trình và hoàn thiện code nguồn và lập trình đồ họa QT: Lư Tất Tuấn Đạt (2001220935)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Khởi tạo QGraphicsScene
    scene = new QGraphicsScene(this);
    ui->graphView->setScene(scene);

    // Kết nối sự kiện với hàm xử lý
    connect(ui->drawGraphButton, &QPushButton::clicked, this, &MainWindow::drawGraph);
    connect(ui->chuTrinhButton, &QPushButton::clicked, this, &MainWindow::runGraphAlgorithm);
    connect(ui->dijkstraButton, &QPushButton::clicked, this, &MainWindow::on_dijkstraButton_clicked);
    connect(ui->findHamiltonPathButton, &QPushButton::clicked, this, &MainWindow::on_findHamiltonPathButton_clicked);

    n = 0; // Số đỉnh
    m = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGraph()
{
    // Xóa đồ thị cũ
    scene->clear();

    // Lấy danh sách cạnh từ người dùng
    QString edgeList = ui->edgeListInput->toPlainText();

    // Tách danh sách cạnh thành các thành phần, loại bỏ các phần rỗng
    QStringList edges = edgeList.split('\n', Qt::SkipEmptyParts);

    // Tạo một QMap để lưu trữ các đỉnh và tọa độ của chúng
    QMap<int, QPointF> vertexCoordinates;

    int nodeSize = 23; // Kích thước của các node

    int vertexNumber = 1; // Số thứ tự của đỉnh

    // Vẽ các đỉnh lên đồ thị và lưu thông tin về các cạnh
    QMap<int, QList<int>> adjacencyList;

    foreach (QString edge, edges) {
        QStringList vertices = edge.split(' ', Qt::SkipEmptyParts);
        if (vertices.size() == 2) {
            int vertex1 = vertices[0].toInt();
            int vertex2 = vertices[1].toInt();

            // Kiểm tra xem đỉnh đã được thêm vào map chưa, nếu chưa thì thêm vào
            if (!vertexCoordinates.contains(vertex1)) {
                QPointF pos1(rand() % 300, rand() % 300); // Tạo tọa độ ngẫu nhiên cho đỉnh
                vertexCoordinates[vertex1] = pos1;
                QGraphicsEllipseItem *ellipseItem = scene->addEllipse(pos1.x(), pos1.y(), nodeSize, nodeSize, QPen(), QBrush(Qt::red)); // Vẽ đỉnh
                QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(vertex1)); // Đánh số vào đỉnh
                textItem->setFont(QFont("Arial", 8));
                scene->addItem(textItem);
                textItem->setPos(pos1.x() + (nodeSize - textItem->boundingRect().width()) / 2, pos1.y() + (nodeSize - textItem->boundingRect().height()) / 2);
            }

            if (!vertexCoordinates.contains(vertex2)) {
                QPointF pos2(rand() % 300, rand() % 300);
                vertexCoordinates[vertex2] = pos2;
                QGraphicsEllipseItem *ellipseItem = scene->addEllipse(pos2.x(), pos2.y(), nodeSize, nodeSize, QPen(), QBrush(Qt::red)); // Vẽ đỉnh
                QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(vertex2)); // Đánh số vào đỉnh
                textItem->setFont(QFont("Arial", 8));
                scene->addItem(textItem);
                textItem->setPos(pos2.x() + (nodeSize - textItem->boundingRect().width()) / 2, pos2.y() + (nodeSize - textItem->boundingRect().height()) / 2);
            }

            // Lưu thông tin về cạnh để vẽ đoạn thẳng sau này
            adjacencyList[vertex1].append(vertex2);
            adjacencyList[vertex2].append(vertex1);
        }
    }

    // Vẽ các đoạn thẳng giữa các đỉnh
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
        int vertex1 = it.key();
        QPointF pos1 = vertexCoordinates.value(vertex1);

        for (int vertex2 : it.value()) {
            QPointF pos2 = vertexCoordinates.value(vertex2);
            scene->addLine(pos1.x() + nodeSize / 2, pos1.y() + nodeSize / 2, pos2.x() + nodeSize / 2, pos2.y() + nodeSize / 2);
        }
    }
}

void MainWindow::runGraphAlgorithm()
{
    // Lấy danh sách cạnh từ người dùng
    QString edgeList = ui->edgeListInput->toPlainText();

    // Tách danh sách cạnh thành các thành phần, loại bỏ các phần rỗng
    QStringList edges = edgeList.split('\n', Qt::SkipEmptyParts);

    // Lặp qua danh sách cạnh để xây dựng đồ thị và tính bậc của mỗi đỉnh
    for (const QString& edge : edges) {
        QStringList vertices = edge.split(' ', Qt::SkipEmptyParts);
        if (vertices.size() == 2) {
            int vertex1 = vertices[0].toInt();
            int vertex2 = vertices[1].toInt();

            a[vertex1].insert(vertex2);
            a[vertex2].insert(vertex1);

            bac[vertex1]++;
            bac[vertex2]++;

            n = qMax(n, qMax(vertex1, vertex2));
            m++;
        }
    }

    // Tiến hành kiểm tra chu trình Euler và hiển thị kết quả
    QString resultString;
    if (isConnected() && KiemTraChuTrinhEuler()) {
        resultString = "Đồ thị có chu trình Euler.\n";
            euler(1, true);
    }
    else {

        resultString = "Đồ thị không có chu trình Euler.\n";
        resultString += "Đường đi Euler: ";
        int startNode = 1;
        for (int i = 1; i <= n; ++i) {
            if (bac[i] % 2 != 0) {
                startNode = i;
                break;
            }
        }
        euler(startNode, false);
    }

    ui->dataEdit->append(resultString);

}

bool MainWindow::isConnected() {
    QVector<bool> visited(n + 1, false);
    QStack<int> st;

    st.push(1);
    while (!st.empty()) {
        int x = st.top();
        st.pop();
        visited[x] = true;

        for (int neighbor : a[x]) {
            if (!visited[neighbor]) {
                st.push(neighbor);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

bool MainWindow::KiemTraChuTrinhEuler() {
    if (!isConnected()) {
        return false;
    }

    for (int i = 1; i <= n; ++i) {
        if (bac[i] % 2 != 0) {
            return false;
        }
    }

    return true;
}

void MainWindow::euler(int x, bool isCycle) {
    QStack<int> st;
    QVector<int> result;

    st.push(x);
    while (!st.empty()) {
        int current = st.top();

        if (a[current].isEmpty()) {
            st.pop();
            result.push_back(current);
        } else {
            int next = *a[current].begin();
            st.push(next);
            a[current].remove(next);
            a[next].remove(current);
        }
    }

    if (isCycle) {
        reverse(result.begin(), result.end());
        result.push_back(result.front());
    }


    QString resultString;
    QTextStream stream(&resultString);
    for (int node : result) {
        stream << node << " ";
    }


    ui->dataEdit->setText(resultString);
}

void MainWindow::on_dijkstraButton_clicked() {
    // Lấy danh sách cạnh từ người dùng
    QString edgeList = ui->edgeListInput->toPlainText();

    // Tách danh sách cạnh thành các thành phần, loại bỏ các phần rỗng
    QStringList edges = edgeList.split('\n', Qt::SkipEmptyParts);

    // Xây dựng đồ thị và tính toán đường đi ngắn nhất
    for (const QString& edge : edges) {
        QStringList vertices = edge.split(' ', Qt::SkipEmptyParts);
        if (vertices.size() == 2) {
            int vertex1 = vertices[0].toInt();
            int vertex2 = vertices[1].toInt();

            a[vertex1].insert(vertex2);
            a[vertex2].insert(vertex1);

            n = qMax(n, qMax(vertex1, vertex2));
            m++;
        }
    }

    // Chọn đỉnh xuất phát (có thể sửa để nhập từ người dùng)
    int startVertex = 1;

    // Thực hiện thuật toán Dijkstra và hiển thị kết quả
    dijkstra(startVertex);
}

void MainWindow::dijkstra(int startVertex) {
    QMap<int, int> distance;
    QMap<int, int> previous;
    QSet<int> unvisitedVertices;

    // Khởi tạo khoảng cách và đỉnh trước đó
    for (int i = 1; i <= n; ++i) {
        distance[i] = std::numeric_limits<int>::max();
        previous[i] = -1;
        unvisitedVertices.insert(i);
    }

    distance[startVertex] = 0;

    while (!unvisitedVertices.isEmpty()) {
        int currentVertex = -1;
        int minDistance = std::numeric_limits<int>::max();

        // Tìm đỉnh có khoảng cách ngắn nhất
        for (int vertex : unvisitedVertices) {
            if (distance[vertex] < minDistance) {
                minDistance = distance[vertex];
                currentVertex = vertex;
            }
        }

        if (currentVertex == -1) {
            break;  // Không còn đỉnh có thể đến được
        }

        unvisitedVertices.remove(currentVertex);

        // Cập nhật khoảng cách từ đỉnh hiện tại đến các đỉnh kề
        for (int neighbor : a[currentVertex]) {
            if (unvisitedVertices.contains(neighbor)) {
                int altDistance = distance[currentVertex] + 1;

                if (altDistance < distance[neighbor]) {
                    distance[neighbor] = altDistance;
                    previous[neighbor] = currentVertex;
                }
            }
        }
    }

    // Hiển thị kết quả
    QString resultString = "Đường đi ngắn nhất từ đỉnh " + QString::number(startVertex) + ":\n";

    for (int i = 1; i <= n; ++i) {
        if (i != startVertex) {
            QVector<int> path;
            int currentVertex = i;

            while (currentVertex != -1) {
                path.prepend(currentVertex);
                currentVertex = previous[currentVertex];
            }

            resultString += "Đỉnh " + QString::number(i) + ": ";

            if (path.size() == 1 && path.front() == i) {
                resultString += "Không có đường đi.\n";
            } else {
                for (int vertex : path) {
                    resultString += QString::number(vertex) + " ";
                }
                resultString += "\n";
            }
        }
    }


    ui->dataEdit->append(resultString);
}

void MainWindow::on_findHamiltonPathButton_clicked()
{
    // Lấy danh sách cạnh từ người dùng
    QString edgeList = ui->edgeListInput->toPlainText();

    // Tách danh sách cạnh thành các thành phần, loại bỏ các phần rỗng
    QStringList edges = edgeList.split('\n', Qt::SkipEmptyParts);
    ui->dataEdit->clear();
    // Xây dựng đồ thị và tính toán chu trình/đường đi Hamilton
    for (const QString& edge : edges) {
        QStringList vertices = edge.split(' ', Qt::SkipEmptyParts);
        if (vertices.size() == 2) {
            int vertex1 = vertices[0].toInt();
            int vertex2 = vertices[1].toInt();

            a[vertex1].insert(vertex2);
            a[vertex2].insert(vertex1);

            n = qMax(n, qMax(vertex1, vertex2));
            m++;
        }
    }

    // Thực hiện thuật toán tìm chu trình/đường đi Hamilton và hiển thị kết quả
    QVector<int> result = hamiltonianCycle();

    // Hiển thị kết quả trong dataEdit
    QString resultString = "Chu trình/Đường đi Hamilton: ";
    if (result.isEmpty()) {
        resultString += "Không tồn tại chu trình/đường đi Hamilton.\n";
    } else {
        for (int vertex : result) {
            resultString += QString::number(vertex) + " ";
        }
        resultString += "\n";
    }

    ui->dataEdit->append(resultString);
}

QVector<int> MainWindow::hamiltonianCycle()
{
    QVector<int> path;
    QVector<bool> visited(n + 1, false);
    int count = 1;
    // Bắt đầu từ đỉnh 1
    path.push_back(1);
    visited[1] = true;

    // Gọi hàm đệ quy để tìm chu trình Hamilton
    hamiltonianUtil(1, path, visited, count);

    return path;
}

void MainWindow::hamiltonianUtil(int pos, QVector<int>& path, QVector<bool>& visited, int& count)
{
    if (count == n) {
        // Đã đi qua tất cả các đỉnh, kiểm tra xem có cạnh nối về đỉnh 1 không
        int lastVertex = path.last();
        if (a[lastVertex].contains(1)) {
            path.push_back(1);
            return;
        }
    }

    for (int neighbor : a[pos]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;

            // Kiểm tra xem đỉnh đã được thêm vào path chưa
            if (!path.contains(neighbor)) {
                path.push_back(neighbor);
                count++;

                // Gọi đệ quy để đi tiếp
                hamiltonianUtil(neighbor, path, visited, count);

                // Nếu đã tìm được chu trình Hamilton, thoát khỏi đệ quy
                if (path.size() == n + 1) {
                    return;
                }

                // Quay lui
                visited[neighbor] = false;
                path.pop_back();
                count--;
            }
        }
    }
}
