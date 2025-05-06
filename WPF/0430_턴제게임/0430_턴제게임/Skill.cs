using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0430_턴제게임
{
    internal class Skill
    {
        private string _name;
        public string Name
        {
            get => _name;
            set { _name = value; }
        }
        private int _damage;
        public int Damage
        {
            get => _damage;
            set { _damage = value; }
        }
        private int _pp;
        public int PP
        {
            get => _pp;
            set { _pp = value; }
        }
        private string _description;
        public string Description
        {
            get => _description;
            set { _description = value; }
        }
        public Skill(string name, int damage, int pp, string description)
        {
            _name = name;
            _damage = damage;
            _pp = pp;
            _description = description;
        }
        public string UseSkill()
        {
            // 스킬 사용 로직
            if (_pp > 0)
            {
                _pp--;
                return string.Format($"{_name} 사용! 데미지: {_damage}");
            }
            else
            {
                return string.Format($"{_name}의 PP가 부족합니다!");
            }
        }
        public string RecoverPP(int amount)
        {
            _pp += amount;
            return string.Format($"{_name}의 PP가 {amount} 회복되었습니다. 현재 PP: {_pp}");
        }
        public string GetSkillInfo()
        {
            return string.Format($"스킬 이름: {_name}, 데미지: {_damage}, PP: {_pp}, 설명: {_description}");
        }
    }
}
