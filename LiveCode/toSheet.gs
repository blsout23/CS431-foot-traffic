var id = '1IdoSmLVPkT6HS74ihangyFjHB2AHDXLTzKrgDKChQs4';//docs.google.com/spreadsheetURL/d
var sheet = SpreadsheetApp.openById(id).getActiveSheet();

function doPost(e) {  
  Logger.log("post request");
  var cloudData = JSON.parse(e.postData.contents); // JSON object containing all info coming from IoT Cloud
  var values = cloudData.values; // array of values contained in the JSON payload
  
  // store values from the values array
  var incLength = values.length;
  
  // read timestamp of incoming message
  var timestamp = values[0].updated_at;          // format: yyyy-MM-ddTHH:mm:ss.mmmZ
  var date = new Date(Date.parse(timestamp)); 
  var hour = date.getHours() + 2;
  var weekday = date.getDay() + 2; //return int 0 (sunday) to 6 (saturday)

  for (var i = 0; i < incLength; i++) {
    var temp = sheet.getRange(hour, weekday).getValue();
    sheet.getRange(hour, weekday).setValue(values[i].value + temp);
  }
}

function doGet(e){
  Logger.log("get request");
}