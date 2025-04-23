namespace _0423_키보드로움직이는타원
{
    partial class ColorForm
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
            this.label2 = new System.Windows.Forms.Label();
            this.cb_color_colormodal = new System.Windows.Forms.ComboBox();
            this.btn_colormodal = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txt_color_colormodal = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "색상";
            // 
            // cb_color_colormodal
            // 
            this.cb_color_colormodal.FormattingEnabled = true;
            this.cb_color_colormodal.Location = new System.Drawing.Point(53, 31);
            this.cb_color_colormodal.Name = "cb_color_colormodal";
            this.cb_color_colormodal.Size = new System.Drawing.Size(121, 20);
            this.cb_color_colormodal.TabIndex = 6;
            this.cb_color_colormodal.SelectedIndexChanged += new System.EventHandler(this.cb_color_colormodal_SelectedIndexChanged);
            // 
            // btn_colormodal
            // 
            this.btn_colormodal.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_colormodal.Location = new System.Drawing.Point(365, 102);
            this.btn_colormodal.Name = "btn_colormodal";
            this.btn_colormodal.Size = new System.Drawing.Size(75, 23);
            this.btn_colormodal.TabIndex = 8;
            this.btn_colormodal.Text = "적용";
            this.btn_colormodal.UseVisualStyleBackColor = true;
            this.btn_colormodal.Click += new System.EventHandler(this.btn_colormodal_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txt_color_colormodal);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cb_color_colormodal);
            this.groupBox1.Location = new System.Drawing.Point(25, 11);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(415, 85);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "색상 변경";
            // 
            // txt_color_colormodal
            // 
            this.txt_color_colormodal.Location = new System.Drawing.Point(213, 31);
            this.txt_color_colormodal.Name = "txt_color_colormodal";
            this.txt_color_colormodal.Size = new System.Drawing.Size(120, 21);
            this.txt_color_colormodal.TabIndex = 8;
            // 
            // ColorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(452, 137);
            this.Controls.Add(this.btn_colormodal);
            this.Controls.Add(this.groupBox1);
            this.Name = "ColorForm";
            this.Text = "Color";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cb_color_colormodal;
        private System.Windows.Forms.Button btn_colormodal;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txt_color_colormodal;
    }
}