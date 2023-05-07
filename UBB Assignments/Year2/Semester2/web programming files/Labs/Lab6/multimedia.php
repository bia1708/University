<?php

// php -S localhost:1234 multimedia.php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization, Origin, X-Auth-Token");


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

// set content type
header('Content-Type: application/json');

// get request parameters
$json = file_get_contents('php://input');
$data = json_decode($json, true);

$action = $data['action'];

// Retrieve all titles
if ($action == "getTitles") {
    $sql = "SELECT * FROM Files";
    global $conn;
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
if ($action == "filterTitles") {
    $filter = $data['filter'];
    $sql = "SELECT * FROM Files WHERE Files.path like '%$filter%'";
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
if ($action == "addFile") {
    $title = $data['title'];
    $file_format = $data['file_format'];
    $path = $data['path'];
    $size = $data['size'];

    $sql = "INSERT INTO Files (title, file_format, path, size) VALUES ('$title', '$file_format', '$path', '$size')";

    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    sqlsrv_close($conn);
}

// Remove a file from the collection
if ($action == "removeFile") {
    $title = $data['title'];

    $sql = "DELETE FROM Files WHERE title='$title'";

    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    sqlsrv_close($conn);
}

// Update a file in the collection
if ($action == "updateFile") {
  $title = $data['title'];
  $file_format = $data['file_format'];
  $path = $data['path'];
  $size = $data['size'];

    $sql = "UPDATE Files SET file_format='$file_format', path='$path', size='$size' WHERE title='$title'";
    $stmt = sqlsrv_prepare($conn, $sql);

    if (!$stmt) {
        die("Query preparation failed: " . print_r(sqlsrv_errors()));
    }

    if (!sqlsrv_execute($stmt)) {
        die("Query execution failed: " . print_r(sqlsrv_errors()));
    }

    sqlsrv_close($conn);
}
