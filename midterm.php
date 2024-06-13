<?php
// Database credentials
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "EnvironmentalData";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Handle POST request to store data
if ($_SERVER["REQUEST_METHOD"] == "POST") {
  // Fetch sensor data from POST request
  $temperature = $_POST['temperature'];
  $humidity = $_POST['humidity'];
  $distance = $_POST['distance'];

  // Prepare and execute the insert query
  $stmt = $conn->prepare("INSERT INTO SensorReadings (temperature, humidity, distance) VALUES (?, ?, ?)");
  $stmt->bind_param("ddi", $temperature, $humidity, $distance);

  // Check if the query was successful
  if ($stmt->execute()) {
    echo "New record created successfully";
  } else {
    echo "Error: " . $stmt->error;
  }

  // Close the statement and the connection
  $stmt->close();
  $conn->close();
  // Stop further script execution as it's an API endpoint
  exit();
}

// Fetch the data to display
$sql = "SELECT temperature, humidity, distance, timestamp FROM SensorReadings ORDER BY timestamp DESC";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html>
<head>
  <title>Environmental Data</title>
  <style>
    body {
      font-family: Arial, sans-serif;
    }
    table {
      border-collapse: collapse;
      width: 100%;
      margin: 20px 0;
    }
    th, td {
      border: 1px solid #ddd;
      padding: 8px;
    }
    th {
      background-color: #f2f2f2;
    }
    th, td {
      text-align: left;
    }
    tr:hover {
      background-color: #f1f1f1;
    }
  </style>
</head>
<body>
  <h1>Sensor Readings</h1>
  <table>
    <tr>
      <th>Timestamp</th>
      <th>Temperature (°C)</th>
      <th>Humidity (%)</th>
      <th>Distance (cm)</th>
    </tr>
    <?php
    // Display data in table rows
    if ($result->num_rows > 0) {
      while($row = $result->fetch_assoc()) {
        echo "<tr><td>" . $row["timestamp"]. "</td><td>" . $row["temperature"]. "</td><td>" . $row["humidity"]. "</td><td>" . $row["distance"]. "</td></tr>";
      }
    } else {
      echo "<tr><td colspan='4'>No data available</td></tr>";
    }
    ?>
  </table>
</body>
</html>

<?php
// Close the connection after data retrieval
$conn->close();
?>
