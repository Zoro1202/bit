using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0430_턴제게임
{ 
    class Member
    {
        public string Name { get; set; }
        public float Hp { get; set; }
        public Skill[] Skills { get; set; } = new Skill[4];
        public int Experience { get; set; }
        public int Level { get; set; }
    }
}
