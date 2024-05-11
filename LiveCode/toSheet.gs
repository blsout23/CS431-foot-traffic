// Written by Ben Southwick and Massimo Fontaine
// 4/20/24
// Accepts a POST request from an Arduino Cloud webhook and writes the payload data into a provided Google Sheet.

// spreadsheetURL is the segment between .com/ and /d in the full URL
// ex: docs.google.com/!!! spreadsheetURL !!!/d
var spreadsheetURL = '1IdoSmLVPkT6HS74ihangyFjHB2AHDXLTzKrgDKChQs4'; 
var sheet = SpreadsheetApp.openById(id).getActiveSheet();

// POST REQUEST
function doPost(e) {  
  Logger.log("post request");
  var cloudData = JSON.parse(e.postData.contents); // JSON object containing all info coming from IoT Cloud
  var values = cloudData.values; // array of values contained in the JSON payload
  var incLength = values.length;
  
  // read timestamp of incoming message
  var timestamp = values[0].updated_at; // format: yyyy-MM-ddTHH:mm:ss.mmmZ
  var date = new Date(Date.parse(timestamp)); 
  // date and day determine cell coordinates in the sheet
  var hour = date.getHours() + 2; //add 2 to adjust for headers, etc.
  var weekday = date.getDay() + 2; //getDay() returns int 0 (sunday) to 6 (saturday)

  for (var i = 0; i < incLength; i++) {
    // add ping value from payload to the current recorded value in the sheet
    var temp = sheet.getRange(hour, weekday).getValue();
    sheet.getRange(hour, weekday).setValue(values[i].value + temp);
  }
}

// GET REQUEST
// Do nothing
function doGet(e){
  Logger.log("get request");
}
