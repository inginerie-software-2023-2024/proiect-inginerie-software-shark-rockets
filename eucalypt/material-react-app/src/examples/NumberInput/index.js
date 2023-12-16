import React, { useState } from 'react';

const NumberInput = ({min, max}) => {
  const [value, setValue] = useState('');

  const handleChange = (e) => {
    let newValue = e.target.value.replace(/[^0-9]/g, '');

    // Ensure the value is within the specified range
    if (newValue !== '' && !isNaN(newValue)) {
      newValue = Math.max(min, Math.min(max, parseInt(newValue, 10)));
    }

    setValue(newValue);
    onChange(newValue); // Pass the updated value to the parent component
  };

  return (
    <input
      type="text"
      value={value}
      onChange={handleChange}
      placeholder="Enter a number"
      style={{
        padding: '8px',
        fontSize: '16px',
        margin: '8px',
        borderRadius: '4px',
        border: '1px solid #ccc',
      }}
    />
  );
};

export default NumberInput;