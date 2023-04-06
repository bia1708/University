// document.getElementById("categoryDropdown").addEventListener("click", function() { getTitles(); })
document.getElementById('titleList').innerHTML = getTitles();

function getTitles() {
    $.ajax({
        url: "http://localhost:1233/multimedia.php",
        type: "POST",
        dataType: "text",
        data: {
            action: "getTitles"
        },
        success: function(response) {
            $(document).ready(function() {
                // Get table element
                var table = document.getElementById("titleList");
                var data = JSON.parse(response);

                // Create header row
                var header = "<tr><th>#</th><th>Title</th><th>File Format</th><th>Path</th><th>Size(KB)</th></tr>";

                // Loop through data and add rows to table
                var rows = "";
                $.each(data, function(index, element) {
                    var row = "<tr>" +
                        "<td>" + JSON.stringify(element.fid) + "</td>" +
                        "<td>" + JSON.stringify(element.title) + "</td>" +
                        "<td>" + JSON.stringify(element.file_format) + "</td>" +
                        "<td>" + JSON.stringify(element.path) + "</td>" +
                        "<td>" + JSON.stringify(element.size) + "</td>" +
                        "</tr>";
                    rows += row;
                });

                // Set table HTML to header row + data rows
                table.innerHTML = header + rows;

            });
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
        }
    });
}



// AJAX function for retrieving titles by category or genre
function filterTitles(filter) {
    $.ajax({
        url: "/multimedia.php",
        type: "POST",
        data: {
            action: "filterTitles",
            filter: filter
        },
        success: function(response) {
            $(document).ready(function() {
                // Get table element
                var table = document.getElementById("filteredTable");
                var data = JSON.parse(response);

                // Create header row
                var header = "<tr><th>#</th><th>File Name</th></tr>";

                // Loop through data and add rows to table
                var rows = "";
                var count = 1;
                $.each(data, function(index, element) {
                    var row = "<tr>" +
                        "<td>" + JSON.stringify(count) + "</td>" +
                        "<td>" + JSON.stringify(element.title) + "</td>" +
                        "</tr>";
                    rows += row;
                    count += 1;
                });

                // Set table HTML to header row + data rows
                table.innerHTML = header + rows;
            });
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
        }
    });
}


// AJAX function for adding a new file to the collection
function addFile(title, file_format, path, size) {
    $.ajax({
        url: "/multimedia.php",
        type: "POST",
        data: {
            action: "addFile",
            title: title,
            file_format: file_format,
            path: path,
            size: size
        },
        success: function(response) {
            alert(response);
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
        }
    });
}

// AJAX function for removing a file from the collection
function removeFile(title) {
    $.ajax({
        url: "/multimedia.php",
        type: "POST",
        data: {
            action: "removeFile",
            title: title
        },
        success: function(response) {
            alert(response);
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
        }
    });
}

// AJAX function for updating a file in the collection
function updateFile(title, file_format, path, size) {
    $.ajax({
        url: "/multimedia.php",
        type: "POST",
        data: {
            action: "updateFile",
            title: title,
            file_format: file_format,
            path: path,
            size: size
        },
        success: function(response) {
            alert(response);
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
        }
    });
}