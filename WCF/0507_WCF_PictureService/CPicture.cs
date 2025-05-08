using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Web;

using System.IO;
using System.Web.Services;		// 파일입출력과 관련된 맴버 사용


namespace _0507_WCF_PictureService
{
    internal class CPicture
    {
        public CPicture()
        {
            //CODEGEN: 이 호출은 ASP.NET 웹 서비스 디자이너에 필요합니다.
            InitializeComponent();
        }
        #region Component Designer generated code

        //웹 서비스 디자이너에 필요합니다. 
        private IContainer components = null;

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {

        }
        #endregion
        // 해당 이미지 파일을 서비스해주는 메서드
        [WebMethod] // 웹메소드 속성을 가진다는 것을 명시
        public byte[] GetPicture(string strFileName)
        {
            byte[] bytePic = { 0 }; // 바이트 배열을 하나 만든다.
            try
            {
                // 해당 이미지 파일을 스트림 형식으로 오픈한다.
                FileStream picFileStream = new
             FileStream(@"C:\Inetpub\wwwroot\PictureService\Pics\" + strFileName, FileMode.Open,
             FileAccess.Read, FileShare.Read);

                // 이미지 파일 스트림을 읽을 객체를 하나 만든다.
                BinaryReader picReader = new BinaryReader(picFileStream);
                // 이미지 파일을 바이트 배열에 넣는다.
                bytePic = picReader.ReadBytes(Convert.ToInt32(picFileStream.Length));
                // 파일스트림을 닫는다.
                picFileStream.Close();
                // 이미지 파일이 들어있는 바이트 배열을 리턴한다.
                return bytePic;
            }
            catch
            {
                // 초기값을 그냥 리턴한다.
                return bytePic;
            }
        }

        // 이미지 파일 목록을 리턴해주는 메서드
        [WebMethod]
        public string[] GetPictureList()
        {
            // 이미지 파일이 들어있는 디렉토리에서 파일 이름들을 문자열 배열에 넣는다.
            string[] strPicList = Directory.GetFiles(@"C:\Inetpub\wwwroot\PictureService\Pics\");

            // 파일 경로를 뺀 파일 이름만 다시 추출한다.
            for (int i = 0; i < strPicList.Length; i++)
            {
                FileInfo fi = new FileInfo(strPicList[i]);
                strPicList[i] = fi.Name;
            }
            // 이 이미지 파일 이름들을 리턴한다.
            return strPicList;
        }
        // 클라이언트들이 업로드하는 이미지 파일들을 저장하는 메서드
        [WebMethod]
        public bool UploadPicture(string strFileName, byte[] bytePic)
        {
            try
            {
                // 주어진 이미지 파일의 이름으로 파일을 하나 만든다.
                FileStream writeFileStream = new FileStream(
              @"C:\Inetpub\wwwroot\PictureService\Pics\" + strFileName, FileMode.Create,
              FileAccess.Write);

                // 이 파일에 바이너리를 넣기 위해 BinaryWriter 객체 생성
                BinaryWriter picWriter = new BinaryWriter(writeFileStream);
                // 바이트 배열로 받은 이미지를 파일에 쓴다.
                picWriter.Write(bytePic);
                // 파일스트림을 닫는다.
                writeFileStream.Close();
                // 업로드 성공
                return true;
            }
            catch (Exception e)
            {
                // 업로드 실패
                return false;
            }
        }

    }
}