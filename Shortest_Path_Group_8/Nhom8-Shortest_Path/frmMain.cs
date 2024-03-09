using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Nhom8_Shortest_Path
{
    public partial class frmMain : Form
    {
        private int[,] weightMatrix;
        public frmMain()
        {
            InitializeComponent();
            InitializeWeightMatrix();
        }
        private List<Point> points = new List<Point>();
        private Dictionary<(int, int), int> weights = new Dictionary<(int, int), int>();
        private string mode = "";
        private int selected = -1;
        private Dictionary<(int, int), Color> segmentColors = new Dictionary<(int, int), Color>();


        private void InitializeWeightMatrix()
        {
            // Khởi tạo ma trận trọng số với số hàng và cột mặc định (có thể thay đổi tùy theo ứng dụng).
            const int defaultRowCount = 3;
            const int defaultColumnCount = 3;
            weightMatrix = new int[defaultRowCount, defaultColumnCount];
        }

        private void lvMaTran_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Kiểm tra xem có mục được chọn không.
            if (lvMaTran.SelectedItems.Count > 0)
            {
                // Lấy ListViewItem đang được chọn.
                ListViewItem selectedItem = lvMaTran.SelectedItems[0];

                // Lấy thông tin từ các cột của ListViewItem.
                int rowIndex = selectedItem.Index; // Giả sử chỉ số dòng được lấy từ chỉ số của ListViewItem.
                int columnIndex = 0; // Giả sử chỉ số cột là 0.

                // Cập nhật giá trị trong ma trận trọng số.
                // Giả sử giá trị được lấy từ TextBox hoặc từ các control khác.
                int weightValue = int.Parse(selectedItem.SubItems[columnIndex].Text);
                weightMatrix[rowIndex, columnIndex] = weightValue;

                // Trình chiếu lại ma trận trọng số.
                DisplayWeightMatrix();
            }
        }

        private void DisplayWeightMatrix()
        {
            lvMaTran.Items.Clear(); // Xóa tất cả các mục cũ.

            for (int i = 0; i < weightMatrix.GetLength(0); i++)
            {
                ListViewItem item = new ListViewItem(weightMatrix[i, 0].ToString());

                // Thêm giá trị từ ma trận trọng số vào các cột của ListViewItem.
                for (int j = 1; j < weightMatrix.GetLength(1); j++)
                {
                    item.SubItems.Add(weightMatrix[i, j].ToString());
                }

                // Thêm ListViewItem vào ListView.
                lvMaTran.Items.Add(item);
            }

        }
        private bool IsValidIndex(int index)
        {
            return index >= 0 && index < weightMatrix.GetLength(0);
        }
        private void UpdateWeightMatrix(Point p1, Point p2, int weight)
        {
            int index1 = points.IndexOf(p1);
            int index2 = points.IndexOf(p2);

            // Kiểm tra chỉ số có nằm trong phạm vi của mảng không.
            if (IsValidIndex(index1) && IsValidIndex(index2))
            {
                weightMatrix[index1, index2] = weight;
                weightMatrix[index2, index1] = weight;
            }
            else
            {
                // Thay đổi kích thước mảng nếu cần.
                ResizeWeightMatrix(Math.Max(index1, index2) + 1);

                // Cập nhật giá trị trong mảng.
                weightMatrix[index1, index2] = weight;
                weightMatrix[index2, index1] = weight;
            }
        }
        private void ResizeWeightMatrix(int newSize)
        {
            int[,] newMatrix = new int[newSize, newSize];
            for (int i = 0; i < weightMatrix.GetLength(0) && i < newSize; i++)
            {
                for (int j = 0; j < weightMatrix.GetLength(1) && j < newSize; j++)
                {
                    newMatrix[i, j] = weightMatrix[i, j];
                }
            }
            weightMatrix = newMatrix;
        }
        private void btnPoint_Click(object sender, EventArgs e)
        {
            mode = "Point";
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            mode = "Delete";
        }

        private void btnLine_Click(object sender, EventArgs e)
        {
            mode = "Line";
            selected = -1;
        }

        private void btnMove_Click(object sender, EventArgs e)
        {
            mode = "Move";
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            int x = e.X;
            int y = e.Y;

            switch (mode)
            {
                case "Point":
                    Point p = new Point(x, y);

                    points.Add(p);
                    UpdateComboBoxes();
                    DrawPoint(p);

                    break;

                case "Delete":
                    int index = FindPoint(x, y);

                    if (index != -1)
                    {
                        points.RemoveAt(index);
                        RemoveWeights(index);
                        UpdateComboBoxes();
                        RedrawPictureBox();
                    }

                    break;

                case "Line":
                    index = FindPoint(x, y);
                    if (index != -1)
                    {
                        if (selected == -1)
                        {
                            selected = index;
                            DrawBorder(points[selected], Color.Red);
                        }
                        else
                        {
                            if (selected == index)
                            {
                                selected = -1;
                            }
                            else
                            {
                                bool connected = weights.ContainsKey((selected, index)) || weights.ContainsKey((index, selected));
                                if (!connected)
                                {
                                    frmNhapDoDai form2 = new frmNhapDoDai();
                                    DialogResult result = form2.ShowDialog();
                                    if (result == DialogResult.OK)
                                    {
                                        int weight = form2.Weight;
                                        weights[(selected, index)] = weight;
                                        DrawLine(points[selected], points[index], weight);

                                        // Cập nhật ma trận trọng số sau khi vẽ đoạn thẳng.
                                        weightMatrix[selected, index] = weight;
                                        weightMatrix[index, selected] = weight;

                                        // Trình chiếu lại ma trận trọng số lên ListView.
                                        DisplayWeightMatrix();

                                        selected = -1;
                                    }
                                }
                            }
                        }
                    }
                    break;

                case "Move":
                    index = FindPoint(x, y);
                    if (index != -1)
                    {
                        selected = index;
                    }

                    break;
            }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (mode == "Move" && selected != -1)
            {
                int x = e.X;
                int y = e.Y;
                points[selected] = new Point(x, y);
                RedrawPictureBox();
            }
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            if (mode == "Move" && selected != -1)
            {
                selected = -1;
            }
        }

        private void UpdateComboBoxes()
        {
            cbBD.Items.Clear();
            cbKT.Items.Clear();

            for (int i = 0; i < points.Count; i++)
            {
                cbBD.Items.Add(i + 1);
                cbKT.Items.Add(i + 1);
            }
        }

        private void DrawPoint(Point p)
        {
            Graphics g = pictureBox1.CreateGraphics();
            Pen pen = new Pen(Color.Black);
            g.DrawEllipse(pen, p.X - 10, p.Y - 10, 20, 20);
            Font font = new Font("Arial", 10);
            Brush brush = new SolidBrush(Color.Black);
            int index = points.IndexOf(p);
            g.DrawString((index + 1).ToString(), font, brush, p.X - 5, p.Y - 5);
            brush.Dispose();
            font.Dispose();
            pen.Dispose();
            g.Dispose();
        }


        private void DrawLine(Point p1, Point p2, int weight)
        {
            Graphics g = pictureBox1.CreateGraphics();
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, p1, p2);
            Font font = new Font("Arial", 10);
            Brush brush = new SolidBrush(Color.Black);
            int x = (p1.X + p2.X) / 2;
            int y = (p1.Y + p2.Y) / 2;
            g.DrawString(weight.ToString(), font, brush, x, y);
            EraseBorder(p1);
            EraseBorder(p2);
            brush.Dispose();
            font.Dispose();
            pen.Dispose();
            g.Dispose();

            // Cập nhật ma trận trọng số sau khi vẽ đoạn thẳng.
            UpdateWeightMatrix(p1, p2, weight);

            // Trình chiếu lại ma trận trọng số lên ListView.
            DisplayWeightMatrix();
        }
        private void EraseBorder(Point p)
        {
            Graphics g = pictureBox1.CreateGraphics();
            Pen pen = new Pen(Color.White);
            g.DrawEllipse(pen, p.X - 12, p.Y - 12, 24, 24);
            pen.Dispose();
            g.Dispose();
        }


        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (mode == "Move" && e.Button == MouseButtons.Left)
            {
                int x = e.X;
                int y = e.Y;
                int index = FindPoint(x, y);
                if (index != -1)
                {
                    selected = index;
                }
            }
        }

        private void RedrawPictureBox()
        {
            pictureBox1.Refresh();
            foreach (Point p in points)
            {
                DrawPoint(p);
            }
            foreach (var pair in weights)
            {
                DrawLine(points[pair.Key.Item1], points[pair.Key.Item2], pair.Value);
            }
        }

        private int FindPoint(int x, int y)
        {
            for (int i = 0; i < points.Count; i++)
            {
                Point p = points[i];
                double distance = Math.Sqrt(Math.Pow(x - p.X, 2) + Math.Pow(y - p.Y, 2));
                if (distance < 5)
                {
                    return i;
                }
            }
            return -1;
        }
        private void DrawBorder(Point p, Color color)
        {
            Graphics g = pictureBox1.CreateGraphics();
            Pen pen = new Pen(color);
            g.DrawEllipse(pen, p.X - 12, p.Y - 12, 24, 24);
            pen.Dispose();
            g.Dispose();
        }

        private void RemoveWeights(int index)
        {
            List<(int, int)> keysToRemove = new List<(int, int)>();
            List<(int, int)> keysToUpdate = new List<(int, int)>();

            foreach (var pair in weights)
            {
                var key = pair.Key;
                if (key.Item1 == index || key.Item2 == index)
                {
                    keysToRemove.Add(key);
                }
                else
                {
                    if (key.Item1 > index || key.Item2 > index)
                    {
                        keysToUpdate.Add(key);
                    }
                }
            }
            foreach (var key in keysToRemove)
            {
                weights.Remove(key);
            }
            foreach (var key in keysToUpdate)
            {
                int value = weights[key];
                weights.Remove(key);
                var newKey = (key.Item1 > index ? key.Item1 - 1 : key.Item1, key.Item2 > index ? key.Item2 - 1 : key.Item2);
                weights[newKey] = value;
            }
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            points.Clear();
            weights.Clear();
            cbBD.Items.Clear();
            cbKT.Items.Clear();
            pictureBox1.Refresh();
            mode = "";
            ClearWeightMatrix();
            DisplayWeightMatrix();
            txtLog.Clear();
            selected = -1;
        }

        private void ClearWeightMatrix()
        {
            int size = points.Count;
            weightMatrix = new int[size, size];
        }
        private void openTSM_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text File|*.txt";
            DialogResult result = openFileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                string fileName = openFileDialog.FileName;
                StreamReader reader = new StreamReader(fileName);
                int pointCount = int.Parse(reader.ReadLine());
                points.Clear();
                for (int i = 0; i < pointCount; i++)
                {
                    string[] coordinates = reader.ReadLine().Split();
                    Point p = new Point(int.Parse(coordinates[0]), int.Parse(coordinates[1]));
                    points.Add(p);
                }
                int weightCount = int.Parse(reader.ReadLine());
                weights.Clear();
                for (int i = 0; i < weightCount; i++)
                {
                    string[] data = reader.ReadLine().Split();
                    var key = (int.Parse(data[0]), int.Parse(data[1]));
                    int value = int.Parse(data[2]);
                    weights[key] = value;
                }
                reader.Close();
                UpdateComboBoxes();
                RedrawPictureBox();
            }
        }

        private void saveTSM_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text File|*.txt";
            DialogResult result = saveFileDialog.ShowDialog();

            if (result == DialogResult.OK)
            {
                string fileName = saveFileDialog.FileName;
                StreamWriter writer = new StreamWriter(fileName);
                writer.WriteLine(points.Count);
                for (int i = 0; i < points.Count; i++)
                {
                    writer.WriteLine(points[i].X + " " + points[i].Y);
                }

                writer.WriteLine(weights.Count);
                foreach (var pair in weights)
                {
                    writer.WriteLine(pair.Key.Item1 + " " + pair.Key.Item2 + " " + pair.Value);
                }
                writer.Close();
            }
        }


        private void closeTSM_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void InfoTSM_Click(object sender, EventArgs e)
        {
            frmDSSVNhom8 info = new frmDSSVNhom8();
            info.ShowDialog();
        }


        //================================================================================================================================
        //DIJKSTRA
        private void btnD_Click(object sender, EventArgs e)
        {
            txtLog.Clear();
            // Lấy chỉ số của đỉnh xuất phát và đỉnh kết thúc từ ComboBox
            int startIndex = cbBD.SelectedIndex;
            int endIndex = cbKT.SelectedIndex;

            // Kiểm tra xem đã chọn cả đỉnh xuất phát và đỉnh kết thúc chưa
            if (startIndex == -1 || endIndex == -1)
            {
                MessageBox.Show("Vui lòng chọn cả đỉnh xuất phát và đỉnh kết thúc.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // Kiểm tra xem có đường đi giữa hai đỉnh hay không
            if (!AreVerticesConnected(startIndex, endIndex))
            {
                MessageBox.Show("Hai đỉnh không có đường đi giữa chúng.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            // Xóa màu của tất cả đoạn đường cũ
            ClearAllPathsColors();

            // Thực hiện thuật toán Dijkstra để tìm đường đi ngắn nhất
            Dictionary<int, int> previousVertices;
            int totalDistance = Dijkstra(startIndex, endIndex, out previousVertices);

            // Hiển thị đường đi và độ dài trong txtLog
            DisplayDijkstraPath(previousVertices, startIndex, endIndex, totalDistance);

            // Tô màu cho đoạn đường ngắn nhất
            List<int> shortestPath = ConstructShortestPath(previousVertices, startIndex, endIndex);
            HighlightShortestPath(shortestPath);
        }

        private bool AreVerticesConnected(int startVertex, int endVertex)
        {
            // Kiểm tra xem có đường đi giữa startVertex và endVertex không
            HashSet<int> visited = new HashSet<int>();
            Queue<int> queue = new Queue<int>();

            queue.Enqueue(startVertex);

            while (queue.Count > 0)
            {
                int currentVertex = queue.Dequeue();
                visited.Add(currentVertex);

                for (int i = 0; i < weightMatrix.GetLength(0); i++)
                {
                    if (!visited.Contains(i) && weightMatrix[currentVertex, i] > 0)
                    {
                        queue.Enqueue(i);

                        // Nếu đỉnh hiện tại là đỉnh kết thúc, có đường đi giữa startVertex và endVertex
                        if (i == endVertex)
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        private int Dijkstra(int start, int end, out Dictionary<int, int> previousVertices)
        {
            Dictionary<int, int> distances = new Dictionary<int, int>();
            previousVertices = new Dictionary<int, int>();
            HashSet<int> visited = new HashSet<int>();

            for (int i = 0; i < weightMatrix.GetLength(0); i++)
            {
                distances[i] = int.MaxValue;
            }

            distances[start] = 0;

            while (visited.Count < weightMatrix.GetLength(0))
            {
                int current = -1;
                int minDistance = int.MaxValue;

                for (int i = 0; i < weightMatrix.GetLength(0); i++)
                {
                    if (!visited.Contains(i) && distances[i] < minDistance)
                    {
                        current = i;
                        minDistance = distances[i];
                    }
                }

                if (current == -1)
                {
                    break;
                }

                visited.Add(current);

                for (int i = 0; i < weightMatrix.GetLength(0); i++)
                {
                    if (!visited.Contains(i) && weightMatrix[current, i] > 0)
                    {
                        int newDistance = distances[current] + weightMatrix[current, i];
                        if (newDistance < distances[i])
                        {
                            distances[i] = newDistance;
                            previousVertices[i] = current; // Lưu đỉnh trước đó
                        }
                    }
                }
            }

            return distances[end];
        }

        private string ConstructPath(Dictionary<int, int> previousVertices, int startVertex, int endVertex)
        {
            List<int> path = new List<int>();

            int currentVertex = endVertex;

            while (currentVertex != startVertex)
            {
                path.Add(currentVertex + 1); // Adjust index by adding 1
                if (previousVertices.ContainsKey(currentVertex))
                {
                    currentVertex = previousVertices[currentVertex];
                }
                else
                {
                    // Không tìm thấy đỉnh trước đó, thoát vòng lặp để tránh lỗi
                    break;
                }
            }

            path.Add(startVertex + 1); // Adjust index by adding 1
            path.Reverse();

            // Kiểm tra chiều dài của path
            if (path.Count < 2)
            {
                // Không đủ đỉnh để tạo đường đi, không tính tổng độ dài
                return $"{string.Join(" -> ", path)} độ dài: 0";
            }

            // Tính độ dài tổng của đường đi
            int totalDistance = 0;
            for (int i = 0; i < path.Count - 1; i++)
            {
                int vertex1 = path[i] - 1; // Chuyển từ chỉ số bắt đầu từ 1 sang chỉ số bắt đầu từ 0
                int vertex2 = path[i + 1] - 1; // Chuyển từ chỉ số bắt đầu từ 1 sang chỉ số bắt đầu từ 0

                // Kiểm tra giá trị của path[i] và path[i + 1] có nằm trong phạm vi của mảng không
                if (vertex1 >= 0 && vertex1 < weightMatrix.GetLength(0) &&
                    vertex2 >= 0 && vertex2 < weightMatrix.GetLength(1))
                {
                    totalDistance += weightMatrix[vertex1, vertex2];
                }
                else
                {
                    // Xử lý ngoại lệ hoặc thông báo lỗi tùy thuộc vào yêu cầu của bạn
                    Console.WriteLine("Lỗi: Đỉnh nằm ngoài phạm vi của ma trận trọng số.");
                }
            }

            return $"{string.Join(" -> ", path)} độ dài: {totalDistance}";
        }


        private void DisplayDijkstraPath(Dictionary<int, int> previousVertices, int startVertex, int endVertex, int totalDistance)
        {
            string path = ConstructPath(previousVertices, startVertex, endVertex);
            txtLog.AppendText($"Đường đi từ {startVertex + 1} đến {endVertex + 1}: {path}\n");
        }

        //==============================================================================================================================

        //FLOYD

        private void btnF_Click(object sender, EventArgs e)
        {
            // Perform the Floyd-Warshall algorithm
            int[,] distanceMatrix = FloydWarshall();

            // Display the results
            DisplayFloydWarshallResults(distanceMatrix);

            tomaufloyd();
        }

        private int[,] FloydWarshall()
        {
            int size = weightMatrix.GetLength(0);
            int[,] distanceMatrix = new int[size, size];

            // Initialize distanceMatrix with initial weights
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    distanceMatrix[i, j] = weightMatrix[i, j];
                }
            }

            // Apply the Floyd-Warshall algorithm
            for (int k = 0; k < size; k++)
            {
                for (int i = 0; i < size; i++)
                {
                    for (int j = 0; j < size; j++)
                    {
                        if (distanceMatrix[i, k] != int.MaxValue && distanceMatrix[k, j] != int.MaxValue
                            && distanceMatrix[i, k] + distanceMatrix[k, j] < distanceMatrix[i, j])
                        {
                            distanceMatrix[i, j] = distanceMatrix[i, k] + distanceMatrix[k, j];
                        }
                    }
                }
            }

            return distanceMatrix;
        }

        private void DisplayFloydWarshallResults(int[,] distanceMatrix)
        {

            txtLog.AppendText("Đường Đi Ngắn Nhất Theo Thuật Toán Floyd-Warshall:\n");

            txtLog.AppendText("\r\n");

            for (int i = 0; i < distanceMatrix.GetLength(0); i++)
            {
                for (int j = 0; j < distanceMatrix.GetLength(1); j++)
                {
                    txtLog.AppendText($"{distanceMatrix[i, j]} ");

                    // Thêm dấu cách giữa các số
                    if (j < distanceMatrix.GetLength(1) - 1)
                    {
                        txtLog.AppendText(" ");
                    }
                }

                // Xuống dòng sau mỗi hàng
                txtLog.AppendText("\r\n");
            }

            // Xuống dòng sau bảng
            txtLog.AppendText("\r\n");
        }
        //==================================================================================================================
        //Tô màu
        private void HighlightShortestPath(List<int> path)
        {
            // Xóa màu của tất cả các đoạn đường cũ
            ClearAllPathsColors();

            Graphics g = pictureBox1.CreateGraphics();
            Pen pen = new Pen(Color.Red, 2); // Màu đỏ cho đoạn đường ngắn nhất

            // Tô màu cho đoạn đường mới và lưu màu vào segmentColors
            for (int i = 0; i < path.Count - 1; i++)
            {
                Point p1 = points[path[i] - 1];
                Point p2 = points[path[i + 1] - 1];

                Color segmentColor = pen.Color; // Màu mặc định nếu không tìm thấy màu của đoạn đường
                pen.Color = segmentColor;
                g.DrawLine(pen, p1, p2);

                // Lưu màu của đoạn đường vào segmentColors
                segmentColors[(path[i], path[i + 1])] = segmentColor;
            }

            pen.Dispose();
            g.Dispose();
        }

        private void ClearAllPathsColors()
        {
            RedrawPictureBox();
        }

        private List<int> ConstructShortestPath(Dictionary<int, int> previousVertices, int startVertex, int endVertex)
        {
            List<int> path = new List<int>();

            int currentVertex = endVertex;

            while (currentVertex != startVertex)
            {
                path.Add(currentVertex + 1); // Adjust index by adding 1
                if (previousVertices.ContainsKey(currentVertex))
                {
                    currentVertex = previousVertices[currentVertex];
                }
                else
                {
                    // Không tìm thấy đỉnh trước đó, thoát vòng lặp để tránh lỗi
                    break;
                }
            }

            path.Add(startVertex + 1); // Adjust index by adding 1
            path.Reverse();

            return path;
        }

        private void tomaufloyd()
        {
            int startIndex = cbBD.SelectedIndex;
            int endIndex = cbKT.SelectedIndex;

            // Kiểm tra xem đã chọn cả đỉnh xuất phát và đỉnh kết thúc chưa
            if (startIndex == -1 || endIndex == -1)
            {
                MessageBox.Show("Vui lòng chọn cả đỉnh xuất phát và đỉnh kết thúc.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // Kiểm tra xem có đường đi giữa hai đỉnh hay không
            if (!AreVerticesConnected(startIndex, endIndex))
            {
                MessageBox.Show("Hai đỉnh không có đường đi giữa chúng.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            // Xóa màu của tất cả đoạn đường cũ
            ClearAllPathsColors();

            Dictionary<int, int> previousVertices;
            int totalDistance = Dijkstra(startIndex, endIndex, out previousVertices);

            // Tô màu cho đoạn đường ngắn nhất
            List<int> shortestPath = ConstructShortestPath(previousVertices, startIndex, endIndex);
            HighlightShortestPath(shortestPath);
        }

        private void Nhom8TSM_Click(object sender, EventArgs e)
        {
            frmDSSVNhom8 sv = new frmDSSVNhom8();
            sv.Show();
        }

        private void HDSD_Click(object sender, EventArgs e)
        {
            frmHDSD hd = new frmHDSD();
            hd.Show();
        }
    }
}
