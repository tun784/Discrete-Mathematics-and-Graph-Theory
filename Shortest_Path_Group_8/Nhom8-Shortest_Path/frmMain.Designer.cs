
using System;

namespace Nhom8_Shortest_Path
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cbBD = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cbKT = new System.Windows.Forms.ComboBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnF = new System.Windows.Forms.Button();
            this.btnD = new System.Windows.Forms.Button();
            this.lvMaTran = new System.Windows.Forms.ListView();
            this.fileTSM = new System.Windows.Forms.ToolStripMenuItem();
            this.openTSM = new System.Windows.Forms.ToolStripMenuItem();
            this.saveTSM = new System.Windows.Forms.ToolStripMenuItem();
            this.closeTSM = new System.Windows.Forms.ToolStripMenuItem();
            this.InfoTSM = new System.Windows.Forms.ToolStripMenuItem();
            this.Nhom8TSM = new System.Windows.Forms.ToolStripMenuItem();
            this.HDSD = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip2 = new System.Windows.Forms.MenuStrip();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.btnPoint = new System.Windows.Forms.Button();
            this.btnLine = new System.Windows.Forms.Button();
            this.btnMove = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.menuStrip2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.flowLayoutPanel1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cbBD);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cbKT);
            this.groupBox1.Location = new System.Drawing.Point(12, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(224, 126);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Tính đường đi";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(28, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(94, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Điểm kết thúc";
            // 
            // cbBD
            // 
            this.cbBD.FormattingEnabled = true;
            this.cbBD.Location = new System.Drawing.Point(126, 30);
            this.cbBD.Name = "cbBD";
            this.cbBD.Size = new System.Drawing.Size(60, 24);
            this.cbBD.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 17);
            this.label1.TabIndex = 5;
            this.label1.Text = "Điểm bắt đầu";
            // 
            // cbKT
            // 
            this.cbKT.FormattingEnabled = true;
            this.cbKT.Location = new System.Drawing.Point(126, 79);
            this.cbKT.Name = "cbKT";
            this.cbKT.Size = new System.Drawing.Size(60, 24);
            this.cbKT.TabIndex = 4;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(5)))), ((int)(((byte)(85)))), ((int)(((byte)(85)))));
            this.panel1.Controls.Add(this.groupBox2);
            this.panel1.Controls.Add(this.lvMaTran);
            this.panel1.Controls.Add(this.groupBox1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.Location = new System.Drawing.Point(0, 28);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(249, 459);
            this.panel1.TabIndex = 3;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnF);
            this.groupBox2.Controls.Add(this.btnD);
            this.groupBox2.Location = new System.Drawing.Point(12, 148);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(224, 101);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Thuật toán";
            // 
            // btnF
            // 
            this.btnF.BackColor = System.Drawing.Color.White;
            this.btnF.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnF.Location = new System.Drawing.Point(126, 38);
            this.btnF.Name = "btnF";
            this.btnF.Size = new System.Drawing.Size(75, 36);
            this.btnF.TabIndex = 15;
            this.btnF.Text = "Floyd";
            this.btnF.UseVisualStyleBackColor = false;
            this.btnF.Click += new System.EventHandler(this.btnF_Click);
            // 
            // btnD
            // 
            this.btnD.BackColor = System.Drawing.Color.White;
            this.btnD.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnD.Location = new System.Drawing.Point(21, 38);
            this.btnD.Name = "btnD";
            this.btnD.Size = new System.Drawing.Size(75, 36);
            this.btnD.TabIndex = 14;
            this.btnD.Text = "Dijkstra";
            this.btnD.UseVisualStyleBackColor = false;
            this.btnD.Click += new System.EventHandler(this.btnD_Click);
            // 
            // lvMaTran
            // 
            this.lvMaTran.BackColor = System.Drawing.Color.White;
            this.lvMaTran.HideSelection = false;
            this.lvMaTran.Location = new System.Drawing.Point(12, 255);
            this.lvMaTran.Name = "lvMaTran";
            this.lvMaTran.Size = new System.Drawing.Size(224, 192);
            this.lvMaTran.TabIndex = 4;
            this.lvMaTran.UseCompatibleStateImageBehavior = false;
            // 
            // fileTSM
            // 
            this.fileTSM.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openTSM,
            this.saveTSM,
            this.closeTSM});
            this.fileTSM.Image = ((System.Drawing.Image)(resources.GetObject("fileTSM.Image")));
            this.fileTSM.Name = "fileTSM";
            this.fileTSM.Size = new System.Drawing.Size(66, 24);
            this.fileTSM.Text = "File";
            // 
            // openTSM
            // 
            this.openTSM.Image = ((System.Drawing.Image)(resources.GetObject("openTSM.Image")));
            this.openTSM.Name = "openTSM";
            this.openTSM.Size = new System.Drawing.Size(129, 26);
            this.openTSM.Text = "Mở";
            this.openTSM.Click += new System.EventHandler(this.openTSM_Click);
            // 
            // saveTSM
            // 
            this.saveTSM.Image = ((System.Drawing.Image)(resources.GetObject("saveTSM.Image")));
            this.saveTSM.Name = "saveTSM";
            this.saveTSM.Size = new System.Drawing.Size(129, 26);
            this.saveTSM.Text = "Lưu";
            this.saveTSM.Click += new System.EventHandler(this.saveTSM_Click);
            // 
            // closeTSM
            // 
            this.closeTSM.Image = ((System.Drawing.Image)(resources.GetObject("closeTSM.Image")));
            this.closeTSM.Name = "closeTSM";
            this.closeTSM.Size = new System.Drawing.Size(129, 26);
            this.closeTSM.Text = "Đóng";
            this.closeTSM.Click += new System.EventHandler(this.closeTSM_Click);
            // 
            // InfoTSM
            // 
            this.InfoTSM.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Nhom8TSM,
            this.HDSD});
            this.InfoTSM.Image = ((System.Drawing.Image)(resources.GetObject("InfoTSM.Image")));
            this.InfoTSM.Name = "InfoTSM";
            this.InfoTSM.Size = new System.Drawing.Size(106, 26);
            this.InfoTSM.Text = "Thông tin";
            // 
            // Nhom8TSM
            // 
            this.Nhom8TSM.Image = ((System.Drawing.Image)(resources.GetObject("Nhom8TSM.Image")));
            this.Nhom8TSM.Name = "Nhom8TSM";
            this.Nhom8TSM.Size = new System.Drawing.Size(224, 26);
            this.Nhom8TSM.Text = "Nhóm 8";
            this.Nhom8TSM.Click += new System.EventHandler(this.Nhom8TSM_Click);
            // 
            // HDSD
            // 
            this.HDSD.Image = ((System.Drawing.Image)(resources.GetObject("HDSD.Image")));
            this.HDSD.Name = "HDSD";
            this.HDSD.Size = new System.Drawing.Size(224, 26);
            this.HDSD.Text = "Hướng dẫn sử dụng";
            this.HDSD.Click += new System.EventHandler(this.HDSD_Click);
            // 
            // menuStrip2
            // 
            this.menuStrip2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(5)))), ((int)(((byte)(85)))), ((int)(((byte)(85)))));
            this.menuStrip2.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileTSM,
            this.InfoTSM});
            this.menuStrip2.Location = new System.Drawing.Point(0, 0);
            this.menuStrip2.Name = "menuStrip2";
            this.menuStrip2.Size = new System.Drawing.Size(800, 28);
            this.menuStrip2.TabIndex = 1;
            this.menuStrip2.Text = "menuStrip2";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.White;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(249, 28);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(551, 318);
            this.pictureBox1.TabIndex = 11;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(5)))), ((int)(((byte)(85)))), ((int)(((byte)(85)))));
            this.flowLayoutPanel1.Controls.Add(this.btnPoint);
            this.flowLayoutPanel1.Controls.Add(this.btnLine);
            this.flowLayoutPanel1.Controls.Add(this.btnMove);
            this.flowLayoutPanel1.Controls.Add(this.btnDelete);
            this.flowLayoutPanel1.Controls.Add(this.btnReset);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(249, 28);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(63, 318);
            this.flowLayoutPanel1.TabIndex = 12;
            // 
            // btnPoint
            // 
            this.btnPoint.BackColor = System.Drawing.Color.White;
            this.btnPoint.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPoint.Image = ((System.Drawing.Image)(resources.GetObject("btnPoint.Image")));
            this.btnPoint.Location = new System.Drawing.Point(3, 3);
            this.btnPoint.Name = "btnPoint";
            this.btnPoint.Size = new System.Drawing.Size(57, 57);
            this.btnPoint.TabIndex = 14;
            this.btnPoint.UseVisualStyleBackColor = false;
            this.btnPoint.Click += new System.EventHandler(this.btnPoint_Click);
            // 
            // btnLine
            // 
            this.btnLine.BackColor = System.Drawing.Color.White;
            this.btnLine.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnLine.Image = ((System.Drawing.Image)(resources.GetObject("btnLine.Image")));
            this.btnLine.Location = new System.Drawing.Point(3, 66);
            this.btnLine.Name = "btnLine";
            this.btnLine.Size = new System.Drawing.Size(57, 57);
            this.btnLine.TabIndex = 13;
            this.btnLine.UseVisualStyleBackColor = false;
            this.btnLine.Click += new System.EventHandler(this.btnLine_Click);
            // 
            // btnMove
            // 
            this.btnMove.BackColor = System.Drawing.Color.White;
            this.btnMove.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMove.Image = ((System.Drawing.Image)(resources.GetObject("btnMove.Image")));
            this.btnMove.Location = new System.Drawing.Point(3, 129);
            this.btnMove.Name = "btnMove";
            this.btnMove.Size = new System.Drawing.Size(57, 57);
            this.btnMove.TabIndex = 0;
            this.btnMove.UseVisualStyleBackColor = false;
            this.btnMove.Click += new System.EventHandler(this.btnMove_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.BackColor = System.Drawing.Color.White;
            this.btnDelete.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDelete.Image = ((System.Drawing.Image)(resources.GetObject("btnDelete.Image")));
            this.btnDelete.Location = new System.Drawing.Point(3, 192);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(57, 57);
            this.btnDelete.TabIndex = 15;
            this.btnDelete.UseVisualStyleBackColor = false;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.White;
            this.btnReset.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnReset.Image = ((System.Drawing.Image)(resources.GetObject("btnReset.Image")));
            this.btnReset.Location = new System.Drawing.Point(3, 255);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(57, 57);
            this.btnReset.TabIndex = 16;
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(5)))), ((int)(((byte)(85)))), ((int)(((byte)(85)))));
            this.groupBox3.Controls.Add(this.txtLog);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.groupBox3.Location = new System.Drawing.Point(249, 346);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(551, 141);
            this.groupBox3.TabIndex = 13;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Log";
            // 
            // txtLog
            // 
            this.txtLog.BackColor = System.Drawing.Color.White;
            this.txtLog.Location = new System.Drawing.Point(6, 21);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.Size = new System.Drawing.Size(539, 114);
            this.txtLog.TabIndex = 14;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 487);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Nhóm 8 (Dijkstra - Floyd)";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.menuStrip2.ResumeLayout(false);
            this.menuStrip2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbBD;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbKT;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ToolStripMenuItem fileTSM;
        private System.Windows.Forms.ToolStripMenuItem openTSM;
        private System.Windows.Forms.ToolStripMenuItem saveTSM;
        private System.Windows.Forms.ToolStripMenuItem InfoTSM;
        private System.Windows.Forms.MenuStrip menuStrip2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ListView lvMaTran;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Button btnMove;
        private System.Windows.Forms.Button btnLine;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnPoint;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox txtLog;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnD;
        private System.Windows.Forms.Button btnF;
        private System.Windows.Forms.ToolStripMenuItem closeTSM;
#pragma warning disable CS0649 // Field 'frmMain.pictureBox1_Click' is never assigned to, and will always have its default value null
        private EventHandler pictureBox1_Click;
        private System.Windows.Forms.ToolStripMenuItem Nhom8TSM;
        private System.Windows.Forms.ToolStripMenuItem HDSD;
#pragma warning restore CS0649 // Field 'frmMain.pictureBox1_Click' is never assigned to, and will always have its default value null
    }
}

