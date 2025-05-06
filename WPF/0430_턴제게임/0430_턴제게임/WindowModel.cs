using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace _0430_턴제게임
{
    internal class WindowModel : INotifyPropertyChanged
    {

        #region 싱글톤 패턴
        public static WindowModel Instance { get; } = new WindowModel();
        private WindowModel() 
        { 
            Test();
        }
        #endregion

        public ObservableCollection<Member> Members { get; set; } = new ObservableCollection<Member>();
        #region 멤버 필드 및 프로퍼티 제공(selectdMember, Name, Phone??)
        private Member _selectedMember;
        public Member SelectedMember
        {
            get => _selectedMember;
            set { _selectedMember = value; OnPropertyChanged(); }
        }
        //public ICollectionView FilteredMembers { get; }

        #endregion

        #region INotifyPropertyChanged 구현
        public event PropertyChangedEventHandler PropertyChanged;
        //일반적인 함수로 구현
        protected void OnPropertyChanged([System.Runtime.CompilerServices.CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        // 같다 (람다식으로 구현)
        //private void OnPropertyChanged([CallerMemberName] string name = null) =>
        //    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        #endregion

        #region TEST 용
        public void Test()
        {
            Members.Add(new Member {
                Name = "홍길동", 
                Hp = 90, 
                Skills = new Skill[4] { 
                    new Skill("불꽃", 10, 5, "불꽃을 쏜다"), 
                    new Skill("물대포", 20, 3, "물대포를 쏜다"), 
                    new Skill("바람", 15, 4, "바람을 쏜다"), 
                    new Skill("전기", 25, 2, "전기를 쏜다") }, 
                Experience = 0, Level = 1 
            });
            SelectedMember = Members[0];
        }
        #endregion
    }
}
