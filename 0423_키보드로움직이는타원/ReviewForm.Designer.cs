namespace _0423_키보드로움직이는타원
{
    partial class ReviewForm
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
            this.btn_start_review = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_start_review
            // 
            this.btn_start_review.Location = new System.Drawing.Point(12, 12);
            this.btn_start_review.Name = "btn_start_review";
            this.btn_start_review.Size = new System.Drawing.Size(75, 23);
            this.btn_start_review.TabIndex = 1;
            this.btn_start_review.Text = "시작";
            this.btn_start_review.UseVisualStyleBackColor = true;
            this.btn_start_review.Click += new System.EventHandler(this.btn_start_review_Click);
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(93, 12);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(695, 45);
            this.trackBar1.TabIndex = 2;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // ReviewForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.btn_start_review);
            this.Name = "ReviewForm";
            this.Text = "ReviewForm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ReviewForm_FormClosed);
            this.Load += new System.EventHandler(this.ReviewForm_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ReviewForm_Paint);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button btn_start_review;
        private System.Windows.Forms.TrackBar trackBar1;
    }
}