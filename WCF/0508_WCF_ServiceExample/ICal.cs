using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace _0508_WCF_ServiceExample
{
	// 참고: "리팩터링" 메뉴에서 "이름 바꾸기" 명령을 사용하여 코드 및 config 파일에서 인터페이스 이름 "IService1"을 변경할 수 있습니다.
	[ServiceContract(CallbackContract =typeof(ICallback))]
	public interface ICal
	{
        [OperationContract(IsOneWay = true)]
		void Add(int a, int b);
		[OperationContract(IsOneWay = true)]
        void Sub(int a, int b);
		[OperationContract(IsOneWay = true)]
        void Mul(int a, int b);
		[OperationContract(IsOneWay = true)]
        void Div(int a, int b);

		// TODO: 여기에 서비스 작업을 추가합니다.

	}

	public interface ICallback
    {
        [OperationContract(IsOneWay = true)]
        void Result(float result);
    }

    // 아래 샘플에 나타낸 것처럼 데이터 계약을 사용하여 복합 형식을 서비스 작업에 추가합니다.
    [DataContract]
	public class CompositeType
	{
		bool boolValue = true;
		string stringValue = "Hello ";

		[DataMember]
		public bool BoolValue
		{
			get { return boolValue; }
			set { boolValue = value; }
		}

		[DataMember]
		public string StringValue
		{
			get { return stringValue; }
			set { stringValue = value; }
		}
	}
}
