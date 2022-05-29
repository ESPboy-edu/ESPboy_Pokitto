// ************************ Drag and drop ***************** //
let dropArea = document.getElementById("drop-area")
let tilesImage = new Image();
var TILE_EMPTY = 0x0;
var TILE_PLAT1 = 0x1;
var TILE_EDGE1 = 0x2;
var TILE_WATER = 0x3;
var TILE_SIGN1 = 0x4;
var TILE_GATE1 = 0x5;
var TILE_METAL = 0x6;
var TILE_SHADE = 0x7;
var TILE_ROCKS = 0x8;
var TILE_BRICK = 0x9;
var TILE_GRASS = 0xA;
var TILE_FUEL1 = 0xB;
var TILE_SAND1 = 0xC;
var TILE_SPIKU = 0xD;
var TILE_SPIKD = 0xE;
var TILE_LEVE1 = 0xF;

// Prevent default drag behaviors
;['dragenter', 'dragover', 'dragleave', 'drop'].forEach(eventName => {
  dropArea.addEventListener(eventName, preventDefaults, false)   
  document.body.addEventListener(eventName, preventDefaults, false)
})

// Highlight drop area when item is dragged over it
;['dragenter', 'dragover'].forEach(eventName => {
  dropArea.addEventListener(eventName, highlight, false)
})

;['dragleave', 'drop'].forEach(eventName => {
  dropArea.addEventListener(eventName, unhighlight, false)
})

// Handle dropped files
dropArea.addEventListener('drop', handleFile, false);

tilesImage.src = "tiles.png";

function preventDefaults (e) {
  e.preventDefault()
  e.stopPropagation()
}

function highlight(e) {
  dropArea.classList.add('highlight')
}

function unhighlight(e) {
  dropArea.classList.remove('active')
}

let uploadProgress = []
let progressBar = document.getElementById('progress-bar')

function initializeProgress(numFiles) {
  progressBar.value = 0
  uploadProgress = []
  
  for(let i = numFiles; i > 0; i--) {
    uploadProgress.push(0)
  }
}

function updateProgress(fileNumber, percent) {
  uploadProgress[fileNumber] = percent
  let total = uploadProgress.reduce((tot, curr) => tot + curr, 0) / uploadProgress.length
  console.debug('update', fileNumber, percent, total)
  progressBar.value = total
}

function handleFile(e) {
  var file = e.target.files[0];
  if (!file) {
    return;
  }
  var reader = new FileReader();
  reader.onload = function(e) {
    var dataView = new DataView(e.target.result);
    var tileData;
    var canvas = document.createElement("canvas");
    var ctx = canvas.getContext("2d");
    let output = document.getElementById('output');
    var width, height, count;
    var i = 32;
    var html = "Name: " + String.fromCharCode.apply(null, new Uint8Array(e.target.result.slice(0, 32))) + "<br/>\n";
    var sign = 0;
    var levelOffsetX, levelOffsetY;
    var playerOffsetX, playerOffsetY;
    width = dataView.getUint8(i++);
    height = dataView.getUint8(i++);
    if (width < 12 || width > 60 || height < 11 || height > 60)
    {
      output.innerHTML = "ERROR: Invalid level";
      return;
    }
    canvas.width = width * 8;
    canvas.height = height * 8;
    tileData = new Uint8Array(width * height);
    html += "Size: " + width + "x" + height + "<br/>\n";
    for (var y = 0; y < height; ++y)
    {
      for (var x = 0; x < width / 2; ++x)
      {
        var tile1 = (dataView.getUint8(i) / 16) & 0xF;
        var tile2 = dataView.getUint8(i++) & 0xF;
        tileData[y * width + x * 2] = tile1;
        tileData[y * width + x * 2 + 1] = tile2;
      }
    }
    count = dataView.getUint8(i++);
    i += count;
    count = dataView.getUint8(i++);
    i += count;
    levelOffsetX = dataView.getInt16(i, true);
    levelOffsetY = dataView.getInt16(i + 2, true);
    playerOffsetX = dataView.getInt16(i + 4, true);
    playerOffsetY = dataView.getInt16(i + 6, true);
    i += 8;
    html += "Fuel: " + dataView.getUint8(i++) * 10 + "<br/>\n";
    html += "Fairs: " + dataView.getUint8(i++) + "<br/>\n";
    //html += "Positions: " + bytes[i++] + "<br/>\n";
    //html += "Gate Left: " + bytes[i++] + "<br/>\n";
    //html += "Gate Right: " + bytes[i++] + "<br/>\n";
    //html += "Gate Interval: " + bytes[i++] * 10 + "<br/>\n";
    output.innerHTML = html;
    output.appendChild(canvas);
    for (var y = 0; y < height; ++y)
    {
      for (var x = 0; x < width; ++x)
      {
        var srcX = tileData[y * width + x] * 8;
        var srcY = 0;
        var srcW = 8;
        var srcH = 8;
        var dstX = x * 8;
        var dstY = y * 8;
        if (tileData[y * width + x] == TILE_SIGN1)
        {
          srcX = sign * 8;
          srcY = 8;
          srcH = 16;
          dstY -= 8;
          ++sign;
          //ctx.drawImage(tilesImage, sign++ * 8, 8, 8, 16, y * 8 - 8, x * 8, 8, 16);
        }
        else if (tileData[y * width + x] == TILE_GATE1)
        {
          //if (x > 0 && tileData[y * width + x - 1] == TILE_GATE1)
          //  ctx.drawImage(tilesImage, tileData[y * width + x] * 8, 0, 8, 8, x * 8, y * 8, 8, 8);
          //else if (x < width - 1 && tileData[y * width + x + 1] == TILE_GATE1)
          //  ctx.drawImage(tilesImage, tileData[y * width + x] * 8, 0, 8, 8, x * 8, y * 8, 8, 8);
          if (y > 0 && tileData[(y - 1) * width + x] == TILE_GATE1)
          {
            srcX = 72;
            srcY = 8;
          }
          //  ctx.drawImage(tilesImage, 72, 8, 8, 8, x * 8, y * 8, 8, 8);
          else if (y < height - 1 && tileData[(y + 1) * width + x] == TILE_GATE1)
          {
            srcX = 72;
            srcY = 8;
          }
          //  ctx.drawImage(tilesImage, 72, 8, 8, 8, x * 8, y * 8, 8, 8);
        }
        //else
        //  ctx.drawImage(tilesImage, tileData[y * width + x] * 8, 0, 8, 8, x * 8, y * 8, 8, 8);
        ctx.drawImage(tilesImage, srcX, srcY, srcW, srcH, dstX, dstY, srcW, srcH);
      }
    }
    ctx.drawImage(tilesImage, 80, 8, 17, 11, playerOffsetX - levelOffsetX, playerOffsetY - levelOffsetY, 17, 11);
    //TODO: Parse file
  };
  reader.readAsArrayBuffer(file);
}
