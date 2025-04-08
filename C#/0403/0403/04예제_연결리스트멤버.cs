namespace _0403
{
    internal class List_Sample
    {
        private LinkedList<Member> datas = new LinkedList<Member>();
        #region 1. 저장
        public void add_test()
        {
            datas.AddLast(new Member("홍길동", "010-2312-1234"));
            datas.AddLast(new Member("김수철", "010-1234-0231"));
            datas.AddLast(new Member("김민재", "010-2332-1234"));
        }
        public void Insert_test()
        {
            // Insert(위치, 값) : 위치에 값을 삽입, count를 넘어가면 예외 발생

            datas.AddBefore(datas.First.Next.Next, new Member("이민수", "010-4412-1234"));
        }
        #endregion
        #region 2. 삭제
        public void Remove_test()
        {
            String selectphone = "010-1234-0231";
            LinkedListNode<Member> node = datas.First;
            bool ret = datas.Remove(node.Next.Value);
            if (ret == true)
            {
                Console.WriteLine("삭제 성공");
            }
            else
            {
                Console.WriteLine("삭제 실패");
            }
        }
        public void RemoveAt_test()
        {
            // RemoveAt(위치) : 위치에 있는 값을 삭제
            try
            {
                datas.RemoveFirst();
            }
            catch (Exception e)
            {
                Console.WriteLine(e + "삭제할 위치가 없습니다.");
            }
        }
        public void Clear_test()
        {
            // Clear() : 모든 데이터를 삭제
            datas.Clear();
        }
        #endregion
        #region 3. 수정(인덱서 활용)
        public void Update_test()
        {
            LinkedListNode<Member> node = datas.First.Next.Next;
            node.Value.Name = "김민수";
        }
        #endregion
        #region 4. 데이터 저장 여부 확인, 인덱스 획득
        public void DataCheck_test()
        {
            //안씀
        }
        #endregion
        #region 5. 검색(find)
        private Member Findname(string name)
        {
            foreach(var data in datas)
            {
                if (data.Name == name)
                {
                    return data;
                }
            }
            return null;
        }
        public void Select_test()
        {
            String selectname = "홍길동"; 
            Member mem = Findname(selectname);

            if (mem != null)
            {
                Console.WriteLine("찾은 전화번호 : " + mem.Phone);
                Console.WriteLine("찾은 이름 : " + mem.Name);
            }
            else
            {
                Console.WriteLine("전화번호가 없습니다.");
            }

        }
        #endregion

        public void Print()
        {
            Console.Write("저장 개수 : " + datas.Count);
            Console.WriteLine();
            foreach (var data in datas)
            {
                Console.WriteLine(data);
            }
        }
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
            List_Sample list = new List_Sample();
            list.add_test();
            list.Insert_test();
            list.Print();
            list.Remove_test();
            list.Print();
            list.Update_test();
            list.Print();
            list.Select_test();
            list.Clear_test();
            list.Print();
        }
    }
}
