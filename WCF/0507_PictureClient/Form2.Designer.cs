﻿namespace _0507_PictureClient
{
    partial class Form2
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.picturePToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureListLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureUploadUToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.picturePToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // picturePToolStripMenuItem
            // 
            this.picturePToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pictureListLToolStripMenuItem,
            this.pictureUploadUToolStripMenuItem});
            this.picturePToolStripMenuItem.Name = "picturePToolStripMenuItem";
            this.picturePToolStripMenuItem.Size = new System.Drawing.Size(71, 20);
            this.picturePToolStripMenuItem.Text = "Picture(&P)";
            // 
            // pictureListLToolStripMenuItem
            // 
            this.pictureListLToolStripMenuItem.Name = "pictureListLToolStripMenuItem";
            this.pictureListLToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.pictureListLToolStripMenuItem.Text = "Picture List(&L)";
            this.pictureListLToolStripMenuItem.Click += new System.EventHandler(this.pictureListLToolStripMenuItem_Click);
            // 
            // pictureUploadUToolStripMenuItem
            // 
            this.pictureUploadUToolStripMenuItem.Name = "pictureUploadUToolStripMenuItem";
            this.pictureUploadUToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.pictureUploadUToolStripMenuItem.Text = "Picture Upload(&U)";
            this.pictureUploadUToolStripMenuItem.Click += new System.EventHandler(this.pictureUploadUToolStripMenuItem_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form2";
            this.Text = "Form2";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form2_Paint);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem picturePToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pictureListLToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pictureUploadUToolStripMenuItem;
    }
}