# Classy Json Schema

Generate PO&lt;T>O's for any language using a template file.

![Classy Json Schema](docs/main-window.png "Classy Json Schema")

## Requirements
- Hunter
- Qt
- cmake

## Build
```
git clone https://github.com/asaladino/classy-json-schema.git
cd classy-json-schema
cmake .
make
./classy_json_schema 
```

## Parameters
```
./classy_json_schema

--templateFile
"/path/to/classy-json-schema/tests/templates/DataModel.java"
--schemaFolder
"/path/to/schema/"
--outputFolder
"/path/to/classy-json-schema/tests/output/java/"
--outputType
"java"
--cli
```