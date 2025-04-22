namespace _0422_윈폼마우스이벤트
{
    partial class Form1
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
            this.menuItem_FileOpen = new System.Windows.Forms.Button();
            this.m_OriginalPannel = new System.Windows.Forms.Panel();
            this.m_SmallPannel = new System.Windows.Forms.Panel();
            this.btn_Minus = new System.Windows.Forms.Button();
            this.btn_Plus = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // menuItem_FileOpen
            // 
            this.menuItem_FileOpen.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.menuItem_FileOpen.Location = new System.Drawing.Point(713, 12);
            this.menuItem_FileOpen.Name = "menuItem_FileOpen";
            this.menuItem_FileOpen.Size = new System.Drawing.Size(75, 23);
            this.menuItem_FileOpen.TabIndex = 1;
            this.menuItem_FileOpen.Text = "파일 열기";
            this.menuItem_FileOpen.UseVisualStyleBackColor = true;
            this.menuItem_FileOpen.Click += new System.EventHandler(this.menuItem_FileOpen_Click);
            // 
            // m_OriginalPannel
            // 
            this.m_OriginalPannel.AutoSize = true;
            this.m_OriginalPannel.Location = new System.Drawing.Point(12, 12);
            this.m_OriginalPannel.Name = "m_OriginalPannel";
            this.m_OriginalPannel.Size = new System.Drawing.Size(322, 226);
            this.m_OriginalPannel.TabIndex = 3;
            this.m_OriginalPannel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.m_OriginalPannel_MouseDown);
            this.m_OriginalPannel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.m_OriginalPannel_MouseMove);
            this.m_OriginalPannel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.m_OriginalPannel_MouseUp);
            // 
            // m_SmallPannel
            // 
            this.m_SmallPannel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.m_SmallPannel.AutoSize = true;
            this.m_SmallPannel.Location = new System.Drawing.Point(490, 237);
            this.m_SmallPannel.Name = "m_SmallPannel";
            this.m_SmallPannel.Size = new System.Drawing.Size(298, 201);
            this.m_SmallPannel.TabIndex = 4;
            // 
            // btn_Minus
            // 
            this.btn_Minus.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_Minus.Location = new System.Drawing.Point(760, 70);
            this.btn_Minus.Name = "btn_Minus";
            this.btn_Minus.Size = new System.Drawing.Size(28, 23);
            this.btn_Minus.TabIndex = 5;
            this.btn_Minus.Text = "-";
            this.btn_Minus.UseVisualStyleBackColor = true;
            this.btn_Minus.Click += new System.EventHandler(this.btn_Minus_Click);
            // 
            // btn_Plus
            // 
            this.btn_Plus.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_Plus.Location = new System.Drawing.Point(760, 41);
            this.btn_Plus.Name = "btn_Plus";
            this.btn_Plus.Size = new System.Drawing.Size(28, 23);
            this.btn_Plus.TabIndex = 6;
            this.btn_Plus.Text = "+";
            this.btn_Plus.UseVisualStyleBackColor = true;
            this.btn_Plus.Click += new System.EventHandler(this.btn_Plus_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btn_Plus);
            this.Controls.Add(this.btn_Minus);
            this.Controls.Add(this.m_SmallPannel);
            this.Controls.Add(this.m_OriginalPannel);
            this.Controls.Add(this.menuItem_FileOpen);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button menuItem_FileOpen;
        private System.Windows.Forms.Panel m_OriginalPannel;
        private System.Windows.Forms.Panel m_SmallPannel;
        private System.Windows.Forms.Button btn_Minus;
        private System.Windows.Forms.Button btn_Plus;
    }
}

