import { Fq, Fr, Point } from '../types/index.js';
import { newBarretenbergApiSync } from '../factory/index.js';
import { BarretenbergApiSync } from './index.js';

describe('env', () => {
  let api: BarretenbergApiSync;

  beforeAll(async () => {
    api = await newBarretenbergApiSync();
  }, 15000);

  afterAll(async () => {
    await api.destroy();
  });

  // it('thread test', async () => {
  //   // Main thread doesn't do anything in this test, so -1.
  //   const threads = (await api.getNumThreads()) - 1;
  //   const iterations = 100000;
  //   const result = await api.testThreads(threads, iterations);
  //   expect(result).toBe(iterations);
  // });

  it('should do point scalar multiplication', () => {
    const x = new Fq(BigInt('9488384720951639809707572357479649241125593886843713801844655093259905475658'));
    const y = new Fq(BigInt('16159185574012703085953752536106955829175932087014915348648613830635631153829'))
    const point = new Point(x, y);
    const scalar = new Fr(BigInt('886568852500438792437990774500261955780191638273449720129821949540731274186'));
    const expectedX = "21120368172291655065856006633228538203884179246857885150190656290063730059746";
    const expectedY = "19186559045587598259773312139908853461953748737889048559842541534575461258344";
    const [resultX, resultY] = api.pointScalar(point as any, scalar);
    expect(resultX.value.toString(10)).toEqual(expectedX);
    expect(resultY.value.toString(10)).toEqual(expectedY);
  });
});
