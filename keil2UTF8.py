
import os
import sys
import chardet
import codecs
from tqdm import tqdm
import warnings

def convert_to_utf8(file_path):
    try:
        content = open(file_path, 'rb').read()
        source_encoding = chardet.detect(content)['encoding']
        if source_encoding is not None:
            if source_encoding.lower() != 'utf-8':
                content = content.decode(source_encoding, 'ignore')
                with codecs.open(file_path, 'wb') as file:
                    file.write(content.encode('utf-8', errors='ignore'))
    except PermissionError as e:
        return f'Skipped: {file_path} (Permission denied)'

def count_files(root_dir):
    count = 0
    for root, dirs, files in os.walk(root_dir):
        count += len(files)
    return count

def convert_directory(root_dir):
    log_file = 'conversion_log.txt'
    exclude_dir = os.path.join(root_dir, 'output')
    
    total_files = count_files(root_dir)
    
    with open(log_file, 'w', encoding='utf-8') as log:
        progress_bar = tqdm(total=total_files, desc='Converting files', unit='file')
        
        def custom_showwarning(message, category, filename, lineno, file=None, line=None):
            log.write(f'WARNING: {message}\n')
        
        warnings.showwarning = custom_showwarning
        
        try:
            for root, dirs, files in os.walk(root_dir):
                if exclude_dir in dirs:
                    dirs.remove(exclude_dir)
                
                for file in files:
                    file_path = os.path.join(root, file)
                    log.write(f'Converting: {file_path}\n')
                    result = convert_to_utf8(file_path)
                    if result is not None:
                        print(result)
                        log.write(f'Skipped: {file_path} (Permission denied)\n')
                    
                    progress_bar.update(1)
        except KeyboardInterrupt:
            warnings.warn("Conversion process interrupted by user.")
        
        progress_bar.close()

if __name__ == '__main__':
    if len(sys.argv) > 1:
        root_directory = sys.argv[1]
        convert_directory(root_directory)
