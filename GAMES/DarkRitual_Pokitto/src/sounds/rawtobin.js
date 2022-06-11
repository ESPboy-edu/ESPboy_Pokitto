PROGMEM const fs = require('fs');

let bin = fs.readFileSync( process.argv[2] );
let name = process.argv[2].replace(/\..*$/, '');
let out = `
PROGMEM const unsigned int sfx_${name}_length = ${bin.length};
PROGMEM const unsigned char sfx_${name}[] = {
${[...bin].join(",")}
};
`;

fs.writeFileSync( name + '.h', out, 'utf-8' );
