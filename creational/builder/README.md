# Builder Pattern
- A builder is a separate component for building an object
- Can either give buidler a constructor or return it via static function
- To make a builder fluent, return `this`
- Different facets of an object can be built with different builders working in tandem via a base class
