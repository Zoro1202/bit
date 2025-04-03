//wbarray.cs
using System;
using System.Collections.Generic;
using WoosongBit41.Data;

namespace WoosongBit41.Lib
{
    internal class WbArray
    {
        #region 1. 맴버 필드 및 프로퍼티, 배열의 인덱서
        private List<object> arr;  // 동적 배열의 주소 저장(저장소)	
        public List<object> Arr { get { return arr; } }
        public object this[int idx]
        {
            get 
            {
                if (idx < 0 || idx >= arr.Count)
                    throw new Exception("범위를 벗어 났습니다.");
                return arr[idx]; 
            } 
        }
        #endregion

        public void SortByBalance()
        {
            arr.Sort((a, b)=>
            {
                Account acc1 = (Account)a;
                Account acc2 = (Account)b;
                return acc1.Balance.CompareTo(acc2.Balance);
            });
        }
        public void SortByAccNumber()
        {
            arr.Sort((a, b) => { return ((Account)a).Number.CompareTo(((Account)b).Number); });
        }
        public void SortByName()
        {
            arr.Sort((a, b) => { return ((Account)a).Name.CompareTo(((Account)b).Name); });
        }

        #region 2. 생성자 
        public WbArray()
        {
            arr = new List<object>();
        }
        #endregion

        #region 기능 메서드
        public void Add(object value)
        {
            arr.Add(value);
        }
        public void Clear()
        {
            arr.Clear();
        }
        
        public void Remove(int idx)
        {
            if (idx < 0 || idx >= arr.Count)
                throw new Exception("잘못된 인덱스 입니다.");  
            arr.RemoveAt(idx);
        }

        #endregion
    }
}
