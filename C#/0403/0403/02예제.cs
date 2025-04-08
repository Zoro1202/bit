using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0403
{
    internal class List_Sample
    {
        private LinkedList<int> datas = new LinkedList<int>();
        #region 1. 저장
        public void add_test()
        {
            for (int i = 1; i < 10; i++)
            {
                datas.AddLast(i);// 마지막에 추가
            }
        }
        public void Insert_test()
        {
            // Insert(위치, 값) : 위치에 값을 삽입, count를 넘어가면 예외 발생
            datas.AddBefore(datas.First.Next.Next, 100);
        }
        #endregion
        #region 2. 삭제
        public void Remove_test()
        {
            // Remove(값) : 값이 있는 위치를 찾아서 삭제
            bool ret = datas.Remove(100);
            // RemoveFirst() : 첫 번째 값을 삭제
            datas.RemoveFirst();
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
            LinkedListNode<int> node = datas.First.Next.Next;
            node.Value = 3000;
        }
        #endregion
        #region 4. 데이터 저장 여부 확인, 인덱스 획득
        public void DataCheck_test()
        {
            // Contains(값) : 값이 있는지 확인
            bool ret = datas.Contains(100);
            if (ret)
            {
                Console.WriteLine("100이 있습니다.");

            }
            else
            {
                Console.WriteLine("100이 없습니다.");
            }
        }
        #endregion
        #region 5. 검색(find)
        public void Select_test()
        {
            //람다식 활용
            // Find(조건) : 조건에 맞는 첫 번째 값을 찾음
            //int value = datas.Find(n => n == 100); // 이거 왜 안되지

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
    internal class Program
    {
        static void Main(string[] args)
        {
            List_Sample list = new List_Sample();
            list.add_test();
            list.Insert_test();
            list.Print();
            list.Remove_test();
        }
    }
}

