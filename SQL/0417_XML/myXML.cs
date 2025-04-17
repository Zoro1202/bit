using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _0417_XML
{
    class myXML
    {
        public void Sample(string str)
        {
            XmlUrlResolver resolver = new XmlUrlResolver();
            resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;

            XmlReaderSettings settings = new XmlReaderSettings();
            settings.XmlResolver = resolver;

            XmlReader reader = XmlReader.Create(str, settings);
            WriteConsole(reader);
            reader.Close();
        }
        private void WriteConsole(XmlReader reader)
        {
            XmlWriter xwriter = XmlWriter.Create(Console.Out);
            xwriter.WriteNode(reader, false);
            xwriter.Close();
            Console.WriteLine();
        }
    }
}
