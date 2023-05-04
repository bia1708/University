using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Spotify
{
    public partial class Form1 : Form
    {
        private DataSet dataSet = new DataSet();
        private SqlConnection dbConnection;

        private SqlDataAdapter dataAdapterParent, dataAdapterChild;
        private readonly BindingSource bindingSourceParent = new BindingSource();
        private readonly BindingSource bindingSourceChild = new BindingSource();


        private void InitializeDatabase()
        {
            String connectionString = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
            String database = ConfigurationManager.AppSettings["Database"];

            this.dbConnection = new SqlConnection("Data Source = MUSHU\\SQLEXPRESS; Initial Catalog = Spotify; Integrated Security = True");
            this.dataAdapterParent = new SqlDataAdapter(ConfigurationManager.AppSettings["SelectParent"], this.dbConnection);
            this.dataAdapterChild = new SqlDataAdapter(ConfigurationManager.AppSettings["SelectChild"], this.dbConnection);

            new SqlCommandBuilder(this.dataAdapterChild);
            new SqlCommandBuilder(this.dataAdapterParent).GetInsertCommand();

            this.dataAdapterParent.Fill(this.dataSet, ConfigurationManager.AppSettings["ParentTableName"]);
            this.dataAdapterChild.Fill(this.dataSet, ConfigurationManager.AppSettings["ChildTableName"]);

            var dataRelation = new DataRelation(
                ConfigurationManager.AppSettings["ForeignKey"],
                this.dataSet.Tables[ConfigurationManager.AppSettings["ParentTableName"]].Columns[ConfigurationManager.AppSettings["ParentReferencedKey"]],
                this.dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Columns[ConfigurationManager.AppSettings["ChildForeignKey"]]);
            this.dataSet.Relations.Add(dataRelation);
        }

        private void InitializeUI()
        {
            this.bindingSourceParent.DataSource = this.dataSet;
            this.bindingSourceParent.DataMember = ConfigurationManager.AppSettings["ParentTableName"];

            this.bindingSourceChild.DataSource = this.bindingSourceParent;
            this.bindingSourceChild.DataMember = ConfigurationManager.AppSettings["ForeignKey"];

            this.dataGridView1.DataSource = this.bindingSourceParent;
            this.dataGridView2.DataSource = this.bindingSourceChild;

            this.label1.Text = ConfigurationManager.AppSettings["ChildTableName"] + " Name: ";

        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Update
            this.dataAdapterChild.Update(this.dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
            this.dataAdapterParent.Update(this.dataSet, ConfigurationManager.AppSettings["ParentTableName"]);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Refresh
            this.dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Clear();
            this.dataSet.Tables[ConfigurationManager.AppSettings["ParentTableName"]].Clear();
            this.dataAdapterParent.Fill(this.dataSet, ConfigurationManager.AppSettings["ParentTableName"]);
            this.dataAdapterChild.Fill(this.dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // Add child record
            DataRow newChildRow = this.dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].NewRow();

            int childID = 0;
            string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
            string childTableID = ConfigurationManager.AppSettings["ChildTableID"];
            string childTableColumn = ConfigurationManager.AppSettings["ChildTableCol"];
            string parentTableID = ConfigurationManager.AppSettings["ParentReferencedKey"];


            using (SqlConnection connection1 = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString))
            {
                string query = string.Format("SELECT MAX({0}) FROM {1}", childTableID, childTableName);
                SqlCommand command = new SqlCommand(query, connection1);

                connection1.Open();
                object result = command.ExecuteScalar();

                if (result != DBNull.Value && result != null)
                {
                    childID = Convert.ToInt32(result) + 1;
                }
            }

            // set the values for the new album row
            newChildRow[childTableColumn] = this.textBox1.Text;
            int parentID = this.dataGridView1.CurrentCell.RowIndex + 1; 
            newChildRow[parentTableID] = parentID;
            newChildRow[childTableID] = childID;

            this.dataSet.Tables[childTableName].Rows.Add(newChildRow);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            // Delete child record
            if (dataGridView2.CurrentRow == null) 
                return;

            DataRowView childRowView = (DataRowView)dataGridView2.CurrentRow.DataBoundItem;
            DataRow childRow = childRowView.Row;
            childRow.Delete();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            // Update child record
            string childTableID = ConfigurationManager.AppSettings["ChildTableID"];
            string childTableColumn = ConfigurationManager.AppSettings["ChildTableCol"];

            if (dataGridView2.CurrentRow == null) 
                return;

            DataRowView childRowView = (DataRowView)dataGridView2.CurrentRow.DataBoundItem;
            DataRow childRow = childRowView.Row;

            // the ID of the record you want to delete
            int albumID = Convert.ToInt32(childRow[childTableID]);

            string newText = textBox1.Text;

            childRow[childTableColumn] = newText;
        }


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitializeDatabase();
            InitializeUI();
        }
    }
}
