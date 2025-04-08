using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0403
{
    class Sample
    {
        private Dictionary<string, Member> datas = new Dictionary<string, Member>();
        #region 1. 저장
        public void add_test()
        {
            try
            {
                datas.Add("홍길동", new Member("홍길동", "010-2312-1234"));
                datas.Add("김수철", new Member("김수철", "010-1234-0231"));
                datas.Add("김민재", new Member("김민재", "010-2332-1234"));
            }
            catch (ArgumentException e)
            {
                Console.WriteLine("키가 중복되었습니다.");
            }
        }
        public void add2_test()
        {
            //추가
            datas["허길동"] = new Member("허길동", "010-2312-1234");
            //수정 : 키가 중복되면 수정됨
            datas["김민재"] = new Member("킴민동", "010-1313-3239");
        }
        #endregion
        #region 2. 검색
        public void select_test()
        {
            try
            {
                Member member = datas["김민재"];
                Console.WriteLine(member.ToString());
            }
            catch (KeyNotFoundException e)
            {
                Console.WriteLine("키가 없습니다.");
            }
        }
        #endregion
        #region 3. 삭제
        public void Remove_test()
        {
            bool ret = datas.Remove("김민재");
            if(ret == true)
            {
                Console.WriteLine("삭제 성공");
            }
            else
            {
                Console.WriteLine("삭제 실패");
            }
        }
        #endregion
        #region 4. 수정
        public void Update_test()
        {
            datas["허길동"].Phone = "010-9989-8888";
        }
        #endregion
        #region 출력
        public void print_test()
        {
            foreach (var item in datas)
            {
                Console.WriteLine(item.Key + " : " + item.Value);
            }
        } 
        #endregion
    }
    internal class Member
    {
        public string Name { get; set; }
        public string Phone { get; set; }

        public Member(string name, string phone)
        {
            Name = name;
            Phone = phone;
        }
        public override string ToString()
        {
            return "이름 : " + Name + ", 전화번호 : " + Phone;
        }
    }
    
    internal class Program
    {
        static void Main(string[] args)
        {
            Sample sample = new Sample();
            sample.add_test();
            sample.add2_test();
            sample.print_test();
            sample.select_test();
            sample.Remove_test();
            sample.print_test();
            sample.Update_test();
            sample.print_test();
        }
    }
}
