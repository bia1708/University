using SpotifyApp.SpotifyDataSetTableAdapters;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SpotifyApp
{
    public partial class Form1 : Form
    {
        private SqlDataAdapter parentTableAdapter;
        private SqlDataAdapter childTableAdapter;
        private DataSet myDataSet;
        private String connection = "Data Source=MUSHU\\SQLEXPRESS;Initial Catalog=Spotify;Integrated Security=True";
        public Form1()
        {
            InitializeComponent();
            myDataSet = new DataSet();
            
            parentTableAdapter = new SqlDataAdapter("SELECT * FROM Artists", connection);
            childTableAdapter = new SqlDataAdapter("SELECT * FROM Albums", connection);
            parentTableAdapter.Fill(myDataSet, "Artists");
            childTableAdapter.Fill(myDataSet, "Albums");
            DataRelation relation = new DataRelation("MyRelation",
                myDataSet.Tables["Artists"].Columns["aid"],
                myDataSet.Tables["Albums"].Columns["aid"]);
            myDataSet.Relations.Add(relation);
            dataGridView1.DataSource = myDataSet.Tables["Artists"];
            dataGridView1.Visible = true;
            dataGridView2.Visible = false;
            comboBox1.DataSource = myDataSet.Tables["Artists"];
            comboBox1.SelectedIndex = -1;
            comboBox1.DisplayMember = "name";
            comboBox1.ValueMember = "aid";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'spotifyDataSet.Artists' table. You can move, or remove it, as needed.
            this.artistsTableAdapter.Fill(this.spotifyDataSet.Artists);
            // TODO: This line of code loads data into the 'spotifyDataSet.Albums' table. You can move, or remove it, as needed.
            this.albumsTableAdapter.Fill(this.spotifyDataSet.Albums);
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

            //int parentID = (int)comboBox1.SelectedIndex;
            int artistId = Convert.ToInt32(comboBox1.SelectedIndex) + 1;

            // filter the albums data view to show only the albums for the selected artist
            DataView albumsView = new DataView(myDataSet.Tables["Albums"]);

            albumsView.RowFilter = "aid = " + artistId;
            albumsView = new DataView(myDataSet.Tables["Albums"], albumsView.RowFilter, "", DataViewRowState.CurrentRows);

            dataGridView2.DataSource = albumsView;
            dataGridView2.Visible = comboBox1.SelectedIndex != -1;

            //DataRow parentRow = myDataSet.Tables["Artists"].Rows.Find(parentID);
            //dataGridView2.DataSource = parentRow.GetChildRows("MyRelation");
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            // create a new row in the albums table
            DataRow newAlbumRow = myDataSet.Tables["Albums"].NewRow();

            int albumID = 0;

            using (SqlConnection connection1 = new SqlConnection(connection))
            {
                string query = "SELECT MAX(alid) FROM albums";
                SqlCommand command = new SqlCommand(query, connection1);

                connection1.Open();
                object result = command.ExecuteScalar();

                if (result != DBNull.Value && result != null)
                {
                    albumID = Convert.ToInt32(result) + 1;
                }
            }

            // set the values for the new album row
            newAlbumRow["title"] = textBox1.Text;
            int parentID = (int)comboBox1.SelectedIndex + 1;
            newAlbumRow["aid"] = parentID; // the artist ID for this album
            newAlbumRow["alid"] = albumID;

            // add the new row to the albums table
            myDataSet.Tables["Albums"].Rows.Add(newAlbumRow);

            // update the database with the changes
            SqlDataAdapter albumsAdapter = new SqlDataAdapter("SELECT * FROM Albums", connection);
            SqlCommandBuilder builder = new SqlCommandBuilder(albumsAdapter);
            albumsAdapter.Update(myDataSet.Tables["Albums"]);
        }

        private void button2_Click(object sender, EventArgs e)
        {

            // Get the selected child row
            if (dataGridView2.CurrentRow == null) return;
            DataRowView childRowView = (DataRowView)dataGridView2.CurrentRow.DataBoundItem;
            DataRow childRow = childRowView.Row;

            // the ID of the record you want to delete
            int recordIdToDelete = Convert.ToInt32(childRow["alid"]);

            string deleteCommand = "DELETE FROM Albums WHERE alid = @alid";

            using (SqlConnection connection1 = new SqlConnection(connection))
            {
                SqlCommand command = new SqlCommand(deleteCommand, connection1);
                command.Parameters.AddWithValue("@alid", recordIdToDelete);
                connection1.Open();
                int rowsAffected = command.ExecuteNonQuery();
                if (rowsAffected == 1)
                {
                    // Update the remaining records to shift their IDs down by one
                    string updateCommand = "UPDATE Albums SET alid = alid - 1 WHERE alid > @alid";
                    command = new SqlCommand(updateCommand, connection1);
                    command.Parameters.AddWithValue("@alid", recordIdToDelete);
                    command.ExecuteNonQuery();
                }
                connection1.Close();
            }

            // Remove the child row from the child data view
            childRowView.Delete();
        }

        private void button3_Click(object sender, EventArgs e)
        {

            if (dataGridView2.CurrentRow == null) return;
            DataRowView childRowView = (DataRowView)dataGridView2.CurrentRow.DataBoundItem;
            DataRow childRow = childRowView.Row;

            // the ID of the record you want to delete
            int albumID = Convert.ToInt32(childRow["alid"]);


            string newTitle = textBox1.Text;

            childRow["title"] = newTitle;

            // update the database with the changes
            SqlDataAdapter albumsAdapter = new SqlDataAdapter("SELECT * FROM Albums", connection);
            SqlCommandBuilder builder = new SqlCommandBuilder(albumsAdapter);
            albumsAdapter.Update(myDataSet.Tables["Albums"]);
        }
    }
}
