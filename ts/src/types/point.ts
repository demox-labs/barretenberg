import { Fq } from './index.js';
import { BufferReader } from '../serialize/buffer_reader.js';

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
    return Point.fromBuffer(Buffer.from(address.replace(/^0x/i, ''), 'hex'));
  }

  toBuffer() {
    return Buffer.concat([this.x.toBuffer(), this.y.toBuffer()]);
  }

  toString() {
    return '0x' + this.toBuffer().toString('hex');
  }

  equals(rhs: Point) {
    return this.x.equals(rhs.x) && this.y.equals(rhs.y);
  }
}
