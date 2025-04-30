using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Input;

namespace _0430_턴제게임
{
    class WindowViewModel : INotifyPropertyChanged
    {
        public ObservableCollection<Member> Members { get; set; } = new ObservableCollection<Member>();
        #region 멤버 필드 및 프로퍼티 제공(selectdMember, Name, Phone??)
        private Member _selectedMember;
        public Member SelectedMember
        {
            get => _selectedMember;
            set { _selectedMember = value; OnPropertyChanged(); }
        }

        public ICollectionView FilteredMembers { get; }

        private int _id;
        public int ID
        {
            get => _id;
            set { _id = value; OnPropertyChanged(); }
        }
        private string _name;
        public string Name
        {
            get => _name;
            set { _name = value; OnPropertyChanged(); }
        }

        private float _health;
        public float HP
        {
            get => _health;
            set { _health = value; OnPropertyChanged(); }
        }
        private int _pp;
        public int PP
        {
            get => _pp;
            set { _pp = value; OnPropertyChanged(); }
        }

        //private string _searchText;
        //public string SearchText
        //{
        //    get => _searchText;
        //    set
        //    {
        //        _searchText = value;
        //        OnPropertyChanged();
        //        FilteredMembers.Refresh();  // 필터 갱신
        //    }
        //}

        #endregion  

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged([CallerMemberName] string name = null) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        #region Action 정의
        //public ICommand AddCommand { get; }
        //public ICommand UpdateCommand { get; }
        //public ICommand DeleteCommand { get; }
        public ICommand MenuBossCommand { get; }
        #endregion
        //private int _idCounter = 1;

        public WindowViewModel()
        {
            //AddCommand = new RelayCommand(AddMember);
            //UpdateCommand = new RelayCommand(UpdateMember, () => SelectedMember != null);
            //DeleteCommand = new RelayCommand(DeleteMember, () => SelectedMember != null);
            MenuBossCommand = new RelayCommand(MenuBoss);
            // 필터링을 위한 View 생성
            //FilteredMembers = CollectionViewSource.GetDefaultView(Members);
            //FilteredMembers.Filter = FilterMembers;
        }
        #region 기능 함수
        private void MenuBoss()
        {
            //모달 창 띄워주는 어쩌고
            MainWindow mainWND = new MainWindow();
            mainWND.ShowDialog();
        }
        //private void AddMember()
        //{
        //    Members.Add(new Member { Id = _idCounter++, Name = Name, Phone = Phone });
        //    Name = Phone = string.Empty;
        //}

        //private void UpdateMember()
        //{
        //    if (SelectedMember != null)
        //    {
        //        SelectedMember.Name = Name;
        //        SelectedMember.Phone = Phone;
        //        OnPropertyChanged(nameof(Members));
        //    }
        //}

        //private void DeleteMember()
        //{
        //    if (SelectedMember != null)
        //    {
        //        Members.Remove(SelectedMember);
        //        SelectedMember = null;
        //    }
        //}

        //private bool FilterMembers(object obj)
        //{
        //    if (obj is Member member)
        //    {
        //        if (string.IsNullOrWhiteSpace(SearchText))
        //            return true;

        //        return member.Name.Contains(SearchText) ||
        //             member.Phone.Contains(SearchText);
        //    }
        //    return false;
        //}

        #endregion
    }
    class RelayCommand : ICommand
    {
        private readonly Action _execute;
        private readonly Func<bool> _canExecute;

        public RelayCommand(Action execute, Func<bool> canExecute = null)
        {
            _execute = execute;
            _canExecute = canExecute;
        }

        public bool CanExecute(object parameter) => _canExecute == null || _canExecute();

        public void Execute(object parameter) => _execute();

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }
    }
}
