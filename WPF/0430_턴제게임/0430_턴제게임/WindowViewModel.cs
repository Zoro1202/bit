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
        //모델 참조
        WindowModel _model = WindowModel.Instance;

        //public string Name { get => _model.Name; set { _model.Name = value; OnPropertyChanged(); } }
        public Member SelectedMember
        {
            get => _model.SelectedMember;
            set { _model.SelectedMember = value; OnPropertyChanged(); }
        }
        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged([CallerMemberName] string name = null) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        #region Action 정의
        public ICommand MenuBossCommand { get; }
        #endregion

        public WindowViewModel()
        {
            _model.PropertyChanged += (s, e) =>
            {
                if (e.PropertyName == nameof(_model.SelectedMember))
                {
                    OnPropertyChanged(nameof(SelectedMember));
                }
            };
            MenuBossCommand = new RelayCommand(MenuBoss);

        }
        #region 기능 함수
        private void MenuBoss()
        {
            //모달 창 띄워주는 어쩌고
            MainWindow mainWND = new MainWindow();
            mainWND.ShowDialog();
        }

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
