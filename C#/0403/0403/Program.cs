namespace _0403
{
    internal class List_Sample
    {
        private List<int> datas = new List<int>();
        #region 1. 저장
        public void add_test()
        {
            for (int i = 1; i < 10; i++)
            {
                datas.Add(i);
            }
        }
        public void Insert_test()
        {
            // Insert(위치, 값) : 위치에 값을 삽입, count를 넘어가면 예외 발생
            datas.Insert(0, 100);
            datas.Insert(1, 200);
            datas.Insert(2, 300);
        }
        #endregion
        #region 2. 삭제
        public void Remove_test()
        {
            // Remove(값) : 값이 있는 위치를 찾아서 삭제
            bool ret = datas.Remove(100);
            // RemoveAt(위치) : 위치에 있는 값을 삭제
            try
            {
                datas.RemoveAt(0);
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
            // Update(위치, 값) : 위치에 있는 값을 수정
            datas[0] = 1000;
            datas[1] = 2000;
            datas[2] = 3000;
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
                int idx = datas.IndexOf(100);
                Console.WriteLine("100의 위치 : " + idx);
            }
            else
            {
                Console.WriteLine("100이 없습니다.");
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
