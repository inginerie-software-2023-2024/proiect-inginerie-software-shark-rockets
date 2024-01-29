import { start_job_update_handler, start_task_update_handler, complete_event_handler } from '../src/services/persistor/index';
import sinon from 'sinon';
import { v4 as uuidv4 } from 'uuid';
import { jobModel } from '../src/schemas/job.schema';
import { taskModel } from '../src/schemas/task.schema';


describe('start_job_update_handler', () => {
  it('should create a new job entry and return response', async () => {
    const req = {
      job_uuid: '123',
      // add other required properties
    };

    const saveStub = sinon.stub(jobModel.prototype, 'save').resolves();
    
    const result = await start_job_update_handler(req);

    expect(result.ok).toBe(true);
    expect(saveStub.calledOnce).toBe(true);

    saveStub.restore();
  });

  // Add more tests for error scenarios or other cases
});

describe('start_task_update_handler', () => {
  it('should create a new task entry and return response', async () => {
    const req = {
      task_uuid: '456',
      // add other required properties
    };

    const saveStub = sinon.stub(taskModel.prototype, 'save').resolves();
    
    const result = await start_task_update_handler(req);

    expect(result.ok).toBe(true);
    expect(saveStub.calledOnce).toBe(true);

    saveStub.restore();
  });

  // Add more tests for error scenarios or other cases
});

describe('complete_event_handler', () => {
  it('should update task entry and return response for task completion event', async () => {
    const req = {
      uuid: '789',
      complete_event_type: 1, // task completion
      // add other required properties
    };

    const updateOneStub = sinon.stub(taskModel, 'updateOne').resolves();

    const result = await complete_event_handler(req);

    expect(result.ok).toBe(true);
    expect(updateOneStub.calledOnce).toBe(true);

    updateOneStub.restore();
  });

  // Add more tests for error scenarios or other cases
});