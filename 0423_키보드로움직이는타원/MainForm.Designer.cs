namespace _0423_키보드로움직이는타원
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btn_delete_shape = new System.Windows.Forms.Button();
            this.btn_create_shape = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txt_size_shape = new System.Windows.Forms.TextBox();
            this.txt_ypos_shape = new System.Windows.Forms.TextBox();
            this.txt_xpos_shape = new System.Windows.Forms.TextBox();
            this.cb_color_shape = new System.Windows.Forms.ComboBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.colorCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.btn_review_shape = new System.Windows.Forms.Button();
            this.btn_saveDB_main = new System.Windows.Forms.Button();
            this.txt_idx_list = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cb_idx_list = new System.Windows.Forms.ComboBox();
            this.btn_loadShape_main = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_delete_shape);
            this.groupBox1.Controls.Add(this.btn_create_shape);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txt_size_shape);
            this.groupBox1.Controls.Add(this.txt_ypos_shape);
            this.groupBox1.Controls.Add(this.txt_xpos_shape);
            this.groupBox1.Controls.Add(this.cb_color_shape);
            this.groupBox1.Location = new System.Drawing.Point(34, 106);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(230, 303);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "도형생성 및 삭제";
            // 
            // btn_delete_shape
            // 
            this.btn_delete_shape.Location = new System.Drawing.Point(129, 213);
            this.btn_delete_shape.Name = "btn_delete_shape";
            this.btn_delete_shape.Size = new System.Drawing.Size(75, 23);
            this.btn_delete_shape.TabIndex = 8;
            this.btn_delete_shape.Text = "삭제";
            this.btn_delete_shape.UseVisualStyleBackColor = true;
            this.btn_delete_shape.Click += new System.EventHandler(this.btn_delete_shape_Click);
            // 
            // btn_create_shape
            // 
            this.btn_create_shape.Location = new System.Drawing.Point(24, 213);
            this.btn_create_shape.Name = "btn_create_shape";
            this.btn_create_shape.Size = new System.Drawing.Size(75, 23);
            this.btn_create_shape.TabIndex = 7;
            this.btn_create_shape.Text = "생성";
            this.btn_create_shape.UseVisualStyleBackColor = true;
            this.btn_create_shape.Click += new System.EventHandler(this.btn_create_shape_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 120);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "크기";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 78);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "색상";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "좌표";
            // 
            // txt_size_shape
            // 
            this.txt_size_shape.Location = new System.Drawing.Point(83, 117);
            this.txt_size_shape.Name = "txt_size_shape";
            this.txt_size_shape.Size = new System.Drawing.Size(121, 21);
            this.txt_size_shape.TabIndex = 3;
            // 
            // txt_ypos_shape
            // 
            this.txt_ypos_shape.Location = new System.Drawing.Point(152, 35);
            this.txt_ypos_shape.Name = "txt_ypos_shape";
            this.txt_ypos_shape.Size = new System.Drawing.Size(52, 21);
            this.txt_ypos_shape.TabIndex = 2;
            // 
            // txt_xpos_shape
            // 
            this.txt_xpos_shape.Location = new System.Drawing.Point(83, 35);
            this.txt_xpos_shape.Name = "txt_xpos_shape";
            this.txt_xpos_shape.Size = new System.Drawing.Size(52, 21);
            this.txt_xpos_shape.TabIndex = 1;
            // 
            // cb_color_shape
            // 
            this.cb_color_shape.FormattingEnabled = true;
            this.cb_color_shape.Location = new System.Drawing.Point(83, 75);
            this.cb_color_shape.Name = "cb_color_shape";
            this.cb_color_shape.Size = new System.Drawing.Size(121, 20);
            this.cb_color_shape.TabIndex = 0;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.colorCToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(143, 26);
            // 
            // colorCToolStripMenuItem
            // 
            this.colorCToolStripMenuItem.Name = "colorCToolStripMenuItem";
            this.colorCToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.colorCToolStripMenuItem.Text = "색상 변경(&C)";
            this.colorCToolStripMenuItem.Click += new System.EventHandler(this.colorCToolStripMenuItem_Click);
            // 
            // btn_review_shape
            // 
            this.btn_review_shape.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btn_review_shape.Location = new System.Drawing.Point(189, 415);
            this.btn_review_shape.Name = "btn_review_shape";
            this.btn_review_shape.Size = new System.Drawing.Size(75, 23);
            this.btn_review_shape.TabIndex = 9;
            this.btn_review_shape.Text = "다시보기";
            this.btn_review_shape.UseVisualStyleBackColor = true;
            this.btn_review_shape.Click += new System.EventHandler(this.btn_review_shape_Click);
            // 
            // btn_saveDB_main
            // 
            this.btn_saveDB_main.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btn_saveDB_main.Location = new System.Drawing.Point(129, 17);
            this.btn_saveDB_main.Name = "btn_saveDB_main";
            this.btn_saveDB_main.Size = new System.Drawing.Size(75, 23);
            this.btn_saveDB_main.TabIndex = 10;
            this.btn_saveDB_main.Text = "저장하기";
            this.btn_saveDB_main.UseVisualStyleBackColor = true;
            this.btn_saveDB_main.Click += new System.EventHandler(this.btn_saveDB_main_Click);
            // 
            // txt_idx_list
            // 
            this.txt_idx_list.Location = new System.Drawing.Point(50, 17);
            this.txt_idx_list.Name = "txt_idx_list";
            this.txt_idx_list.Size = new System.Drawing.Size(52, 21);
            this.txt_idx_list.TabIndex = 9;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(21, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(16, 12);
            this.label4.TabIndex = 9;
            this.label4.Text = "ID";
            // 
            // cb_idx_list
            // 
            this.cb_idx_list.FormattingEnabled = true;
            this.cb_idx_list.Location = new System.Drawing.Point(50, 45);
            this.cb_idx_list.Name = "cb_idx_list";
            this.cb_idx_list.Size = new System.Drawing.Size(72, 20);
            this.cb_idx_list.TabIndex = 11;
            // 
            // btn_loadShape_main
            // 
            this.btn_loadShape_main.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btn_loadShape_main.Location = new System.Drawing.Point(129, 43);
            this.btn_loadShape_main.Name = "btn_loadShape_main";
            this.btn_loadShape_main.Size = new System.Drawing.Size(75, 23);
            this.btn_loadShape_main.TabIndex = 12;
            this.btn_loadShape_main.Text = "불러오기";
            this.btn_loadShape_main.UseVisualStyleBackColor = true;
            this.btn_loadShape_main.Click += new System.EventHandler(this.btn_loadShape_main_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(21, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(16, 12);
            this.label5.TabIndex = 13;
            this.label5.Text = "ID";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.btn_loadShape_main);
            this.groupBox2.Controls.Add(this.cb_idx_list);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.txt_idx_list);
            this.groupBox2.Controls.Add(this.btn_saveDB_main);
            this.groupBox2.Location = new System.Drawing.Point(34, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(230, 82);
            this.groupBox2.TabIndex = 14;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "저장 & 불러오기";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.btn_review_shape);
            this.Controls.Add(this.groupBox1);
            this.Name = "MainForm";
            this.Text = "Main";
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.MainForm_MouseClick);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txt_size_shape;
        private System.Windows.Forms.TextBox txt_ypos_shape;
        private System.Windows.Forms.TextBox txt_xpos_shape;
        private System.Windows.Forms.ComboBox cb_color_shape;
        private System.Windows.Forms.Button btn_create_shape;
        private System.Windows.Forms.Button btn_delete_shape;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem colorCToolStripMenuItem;
        private System.Windows.Forms.Button btn_review_shape;
        private System.Windows.Forms.Button btn_saveDB_main;
        private System.Windows.Forms.TextBox txt_idx_list;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cb_idx_list;
        private System.Windows.Forms.Button btn_loadShape_main;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}

