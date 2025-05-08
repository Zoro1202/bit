using System.ServiceModel;

namespace _0507_WCF_PictureService
{
    [ServiceContract]
    public interface IPicture
    {
        [OperationContract]
        byte[] GetPicture(string fileName);
        [OperationContract]
        string[] GetPictureList();
        [OperationContract]
        bool UploadPicture(string fileName, byte[] bytePicture);
    }
}
