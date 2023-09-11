import { Fq } from '../index.js';
import { BufferReader } from '../../serialize/buffer_reader.js';

export class Point {
  static SIZE_IN_BYTES = 64;
  static EMPTY = new Point(Fq.ZERO, Fq.ZERO);

  constructor(public readonly x: Fq, public readonly y: Fq) {}

  static random() {
    // TODO: This is not a point on the curve!
    return new Point(Fq.random(), Fq.random());
  }

  static fromBuffer(buffer: Uint8Array | BufferReader) {
    const reader = BufferReader.asReader(buffer);
    return new this(Fq.fromBuffer(reader), Fq.fromBuffer(reader));
  }

  static fromString(address: string) {
    address = address.replace(/^0x/i, '');
    const byteValues = new Uint8Array(Math.ceil(address.length / 2));
    for (let i = 0; i < byteValues.length; i++) {
      byteValues[i] = Number.parseInt(address.substr(i * 2, 2), 16);
    }
    return Point.fromBuffer(byteValues);
  }

  toBuffer() {
    const xBuffer = this.x.toBuffer();
    const yBuffer = this.y.toBuffer();
    const combined = new Uint8Array(xBuffer.length + yBuffer.length);
    combined.set(xBuffer, 0);
    combined.set(yBuffer, xBuffer.length);
    return combined;
  }

  toString() {
    const buffer = this.toBuffer();
    let hexString = '0x';
    for (let i = 0; i < buffer.length; i++) {
      hexString += buffer[i].toString(16).padStart(2, '0');
    }
    return hexString;
  }

  equals(rhs: Point) {
    return this.x.equals(rhs.x) && this.y.equals(rhs.y);
  }
}
