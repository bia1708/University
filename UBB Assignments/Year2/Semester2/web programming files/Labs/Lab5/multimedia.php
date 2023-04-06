<?php

// php -S localhost:1234 multimedia.php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

$serverName = "MUSHU\SQLEXPRESS";
$connectionOptions = array(
    "Database" => "Multimedia",
);

// Establishes the connection
$conn = sqlsrv_connect($serverName, $connectionOptions);

if ($conn === false) {
    // Handle errors
    echo "Unable to connect.</br>";
    die(print_r(sqlsrv_errors(), true));
}

// Retrieve all titles
if ($_POST["action"] == "getTitles") {
    $sql = "SELECT * FROM Files";

    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    $titles = array();

    while ($row = sqlsrv_fetch_array($stmt, SQLSRV_FETCH_ASSOC)) {
        $titles[] = $row;
    }

    echo json_encode($titles);

    sqlsrv_close($conn);
}

// Retrieve titles by category
if ($_POST["action"] == "filterTitles") {
    $filter = $_POST["filter"];
    $sql = "SELECT Files.title FROM Files WHERE Files.path like '%$filter%'";
    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    $titles = array();

    while ($row = sqlsrv_fetch_array($stmt, SQLSRV_FETCH_ASSOC)) {
        $titles[] = $row;
    }

    echo json_encode($titles);

    sqlsrv_close($conn);
}

// Add a new file to the collection
if ($_POST["action"] == "addFile") {
    $title = $_POST["title"];
    $file_format = $_POST["file_format"];
    $path = $_POST["path"];
    $size = $_POST["size"];

    $sql = "INSERT INTO Files (title, file_format, path, size) VALUES ('$title', '$file_format', '$path', '$size')";

    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    echo "New file added successfully";

    sqlsrv_close($conn);
}

// Remove a file from the collection
if ($_POST["action"] == "removeFile") {
    $title = $_POST["title"];

    $sql = "DELETE FROM Files WHERE title='$title'";

    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    echo "File removed successfully!";

    sqlsrv_close($conn);
}

// Update a file in the collection
if ($_POST["action"] == "updateFile") {
    $title = $_POST["title"];
    $file_format = $_POST["file_format"];
    $path = $_POST["path"];
    $size = $_POST["size"];

    $sql = "UPDATE Files SET file_format='$file_format', path='$path', size='$size' WHERE title='$title'";
    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    echo "File updated successfully!";

    sqlsrv_close($conn);
}

