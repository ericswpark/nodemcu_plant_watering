#ifndef HTMLDAT_H
#define HTMLDAT_H


const char pageMain[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Plant Watering</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        html {
            text-align: center;
        }
        
        button {
            margin: 2px;
            border: none;
            border-radius: 4px;
            padding: 16px 20px;
            font-size: 1.5rem;
        }

        .channel-section {
            margin: 8px;
        }

        .sensor-title {
            font-size: 1.5rem;
        }

        .sensor-value {
            font-size: 1.5rem;
        }
    </style>
  </head>
  <body>
    <div class="channel-section">
      <span class="sensor-title">S1:</span>
      <span class="sensor-value" id="s1">Loading...</span>
      <button onclick="m1Toggle()">Toggle Motor</button>
    </div>

    <div class="channel-section">
      <span class="sensor-title">S2:</span>
      <span class="sensor-value" id="s2">Loading...</span>
      <button onclick="m2Toggle()">Toggle Motor</button>
    </div>

    <div class="channel-section">
      <span class="sensor-title">S3:</span>
      <span class="sensor-value" id="s3">Loading...</span>
      <button onclick="m3Toggle()">Toggle Motor</button>
    </div>

    <div class="channel-section">
      <span class="sensor-title">S4:</span>
      <span class="sensor-value" id="s4">Loading...</span>
      <button onclick="m4Toggle()">Toggle Motor</button>
    </div>
  </body>
  <script>
    for (let chan = 1; chan <= 4; chan++) {
      setInterval(() => {
        fetch(`/s${chan}`)
          .then(response => response.text())
          .then(data => {
            document.getElementById(`s${chan}`).innerHTML = data;
          });
      }, 1000);
    }

    function m1Toggle() {
        fetch("/m1")
          .then(response => response.text())
          .then(data => {
            alert("M1 is now " + data.toLowerCase());
          });
    }

    function m2Toggle() {
        fetch("/m2")
          .then(response => response.text())
          .then(data => {
            alert("M2 is now " + data.toLowerCase());
          });
    }

    function m3Toggle() {
        fetch("/m3")
          .then(response => response.text())
          .then(data => {
            alert("M3 is now " + data.toLowerCase());
          });
    }

    function m4Toggle() {
        fetch("/m4")
          .then(response => response.text())
          .then(data => {
            alert("M4 is now " + data.toLowerCase());
          });
    }
  </script>
</html>
)=====";



#endif