<?php
    include 'header.php'
?>

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/light.css">
<button class="home-button" onclick="location.href='http://localhost/dbKeywords/Authentification/index.php'">Home</button>
<h1>Keyword</h1>

<div class="article-container">
    <?php
        $title = mysqli_real_escape_string($conn, $_GET['title']);
        //$type = mysqli_real_escape_string($conn, $_GET['type']);

        $sql = "SELECT * FROM keyword WHERE Name = '$title'"; /*AND Type = '$type'";*/
        $result = mysqli_query($conn, $sql);
        $queryResults = mysqli_num_rows($result);

        if ($queryResults > 0){
            while ($row = mysqli_fetch_assoc($result)) {
                echo "<div class='article-box'>
                
                <h2>".$row['Name']."</h2> 
                <p class='type'>".$row['Type']."</p>
                <p><b><br>Definition: </b></br>".$row['Definition']."</p>
                <b>Syntaxis: </b>
                <div class='example-box'>
                <pre>".$row['Syntaxis']."</pre>
                </div>

                <b>Example: </b>

                <pre><code>".$row['Example']."</code></pre>
                
                <p><b>C++ version: </b>".$row['cpp_version']."</p>";
                
                echo "<p><b>Related keywords: </b>".$row['Related_keywords']."</p>
                </div>";
            }
        }
        
    ?>
</div>

</body>
</html>