// ========== CANVAS 1: Raycasting Concept ========== 
function drawRaycastingConcept() {
    const canvas = document.getElementById('canvas1');
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    const width = canvas.width || 600;
    const height = canvas.height || 400;
    
    // Set canvas size properly
    canvas.width = width;
    canvas.height = height;
    
    // Background
    ctx.fillStyle = '#0a0e27';
    ctx.fillRect(0, 0, width, height);
    
    // Grid
    ctx.strokeStyle = '#1a3a52';
    ctx.lineWidth = 1;
    const gridSize = 40;
    
    for (let x = 0; x <= width; x += gridSize) {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, height);
        ctx.stroke();
    }
    
    for (let y = 0; y <= height; y += gridSize) {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(width, y);
        ctx.stroke();
    }
    
    // Walls (dark squares)
    ctx.fillStyle = '#8B4513';
    ctx.fillRect(0, 0, width, gridSize); // Top wall
    ctx.fillRect(0, height - gridSize, width, gridSize); // Bottom wall
    ctx.fillRect(0, 0, gridSize, height); // Left wall
    ctx.fillRect(width - gridSize, 0, gridSize, height); // Right wall
    
    // Inner walls
    ctx.fillRect(gridSize * 3, gridSize * 2, gridSize * 2, gridSize);
    ctx.fillRect(gridSize * 4, gridSize * 4, gridSize, gridSize * 3);
    
    // Player position
    const playerX = gridSize * 3.5;
    const playerY = gridSize * 3.5;
    
    ctx.fillStyle = '#00ff00';
    ctx.beginPath();
    ctx.arc(playerX, playerY, 8, 0, Math.PI * 2);
    ctx.fill();
    
    // Player direction
    ctx.strokeStyle = '#00ff00';
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(playerX, playerY);
    ctx.lineTo(playerX + 40, playerY);
    ctx.stroke();
    
    // Raycasting beams (showing 5 rays)
    const raysCount = 9;
    const fov = Math.PI * 0.66;
    
    for (let i = 0; i < raysCount; i++) {
        const angle = -fov / 2 + (fov / (raysCount - 1)) * i;
        const rayLength = 250;
        const endX = playerX + Math.cos(angle) * rayLength;
        const endY = playerY + Math.sin(angle) * rayLength;
        
        // Color gradient for rays
        if (i < Math.floor(raysCount / 2)) {
            ctx.strokeStyle = `rgba(79, 195, 247, ${0.3 + (i / raysCount) * 0.5})`;
        } else if (i === Math.floor(raysCount / 2)) {
            ctx.strokeStyle = 'rgba(233, 69, 96, 0.8)'; // Center ray in red
        } else {
            ctx.strokeStyle = `rgba(79, 195, 247, ${0.8 - ((i - raysCount/2) / raysCount) * 0.5})`;
        }
        
        ctx.lineWidth = 1.5;
        ctx.beginPath();
        ctx.moveTo(playerX, playerY);
        ctx.lineTo(endX, endY);
        ctx.stroke();
    }
    
    // Legend
    ctx.fillStyle = '#eaeaea';
    ctx.font = '12px Arial';
    ctx.fillText('Vue de dessus: Raycasting', 10, height - 10);
    
    ctx.fillStyle = '#00ff00';
    ctx.font = 'bold 12px Arial';
    ctx.fillText('Joueur', playerX + 15, playerY - 10);
    
    // Ray impact points (simplified)
    ctx.fillStyle = 'rgba(233, 69, 96, 0.6)';
    for (let i = 0; i < raysCount; i++) {
        const angle = -fov / 2 + (fov / (raysCount - 1)) * i;
        const rayLength = 150;
        const impactX = playerX + Math.cos(angle) * rayLength;
        const impactY = playerY + Math.sin(angle) * rayLength;
        ctx.beginPath();
        ctx.arc(impactX, impactY, 3, 0, Math.PI * 2);
        ctx.fill();
    }
}

// ========== CANVAS 2: DDA Algorithm Visualization ========== 
function drawDDAVisualization() {
    const canvas = document.getElementById('canvas2');
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    const width = canvas.width || 600;
    const height = canvas.height || 400;
    
    canvas.width = width;
    canvas.height = height;
    
    // Background
    ctx.fillStyle = '#0a0e27';
    ctx.fillRect(0, 0, width, height);
    
    // Grid
    const gridCellSize = 50;
    ctx.strokeStyle = '#1a3a52';
    ctx.lineWidth = 1;
    
    for (let x = 0; x <= width; x += gridCellSize) {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, height);
        ctx.stroke();
    }
    
    for (let y = 0; y <= height; y += gridCellSize) {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(width, y);
        ctx.stroke();
    }
    
    // Draw walls (cells with value 1)
    ctx.fillStyle = '#8B4513';
    const mapWidth = Math.floor(width / gridCellSize);
    const mapHeight = Math.floor(height / gridCellSize);
    
    // Borders
    for (let x = 0; x < mapWidth; x++) {
        ctx.fillRect(x * gridCellSize, 0, gridCellSize, gridCellSize);
        ctx.fillRect(x * gridCellSize, (mapHeight - 1) * gridCellSize, gridCellSize, gridCellSize);
    }
    for (let y = 0; y < mapHeight; y++) {
        ctx.fillRect(0, y * gridCellSize, gridCellSize, gridCellSize);
        ctx.fillRect((mapWidth - 1) * gridCellSize, y * gridCellSize, gridCellSize, gridCellSize);
    }
    
    // Some internal walls
    ctx.fillRect(3 * gridCellSize, 2 * gridCellSize, 2 * gridCellSize, gridCellSize);
    ctx.fillRect(4 * gridCellSize, 4 * gridCellSize, gridCellSize, 2 * gridCellSize);
    
    // Player
    const playerX = 2.5 * gridCellSize;
    const playerY = 2.5 * gridCellSize;
    
    ctx.fillStyle = '#00ff00';
    ctx.beginPath();
    ctx.arc(playerX, playerY, 8, 0, Math.PI * 2);
    ctx.fill();
    
    // Ray direction (center ray going right)
    const rayAngle = 0;
    ctx.strokeStyle = '#e94560';
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(playerX, playerY);
    ctx.lineTo(playerX + 200, playerY);
    ctx.stroke();
    
    // DDA Path visualization
    ctx.strokeStyle = 'rgba(79, 195, 247, 0.7)';
    ctx.lineWidth = 1;
    ctx.setLineDash([5, 5]);
    
    // Simplified DDA path (stepping through grid)
    const dda_points = [
        {x: playerX, y: playerY},
        {x: 3.5 * gridCellSize, y: playerY},
        {x: 4.5 * gridCellSize, y: playerY},
        {x: 5.5 * gridCellSize, y: playerY},
        {x: 6.5 * gridCellSize, y: playerY}
    ];
    
    for (let i = 0; i < dda_points.length - 1; i++) {
        ctx.beginPath();
        ctx.moveTo(dda_points[i].x, dda_points[i].y);
        ctx.lineTo(dda_points[i + 1].x, dda_points[i + 1].y);
        ctx.stroke();
        
        // Draw step markers
        ctx.fillStyle = i === dda_points.length - 2 ? '#e94560' : '#4fc3f7';
        ctx.beginPath();
        ctx.arc(dda_points[i].x, dda_points[i].y, 4, 0, Math.PI * 2);
        ctx.fill();
    }
    
    // Wall hit point
    ctx.fillStyle = '#e94560';
    ctx.beginPath();
    ctx.arc(dda_points[dda_points.length - 1].x, dda_points[dda_points.length - 1].y, 6, 0, Math.PI * 2);
    ctx.fill();
    
    ctx.setLineDash([]);
    
    // Labels
    ctx.fillStyle = '#eaeaea';
    ctx.font = '12px Arial';
    ctx.fillText('DDA: Parcours de grille', 10, height - 10);
    
    ctx.fillStyle = '#00ff00';
    ctx.font = 'bold 11px Arial';
    ctx.fillText('Joueur', playerX + 15, playerY - 10);
    
    ctx.fillStyle = '#e94560';
    ctx.font = 'bold 11px Arial';
    ctx.fillText('Mur!', dda_points[dda_points.length - 1].x + 15, dda_points[dda_points.length - 1].y - 10);
}

// ========== DRAW WALL HEIGHT DIAGRAM ========== 
function drawWallHeightDiagram() {
    const canvas = document.getElementById('canvas3');
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    const width = 600;
    const height = 400;
    
    canvas.width = width;
    canvas.height = height;
    
    // Background
    ctx.fillStyle = '#0a0e27';
    ctx.fillRect(0, 0, width, height);
    
    // Draw 3D walls at different distances
    const distances = [1, 2, 3, 4];
    const baseHeight = 300;
    const spacing = width / (distances.length + 1);
    
    distances.forEach((dist, index) => {
        const x = spacing * (index + 1);
        const wallHeight = baseHeight / dist;
        const wallY = (height - wallHeight) / 2;
        
        // Wall rectangle
        ctx.fillStyle = '#8B4513';
        ctx.fillRect(x - 25, wallY, 50, wallHeight);
        
        // Distance label
        ctx.fillStyle = '#4fc3f7';
        ctx.font = 'bold 12px Arial';
        ctx.fillText(`d=${dist}`, x - 15, height - 10);
        
        // Height annotation
        ctx.strokeStyle = '#e94560';
        ctx.lineWidth = 1;
        ctx.setLineDash([3, 3]);
        ctx.beginPath();
        ctx.moveTo(x - 40, wallY);
        ctx.lineTo(x - 40, wallY + wallHeight);
        ctx.stroke();
        ctx.setLineDash([]);
        
        ctx.fillStyle = '#e94560';
        ctx.font = '10px Arial';
        ctx.fillText(`h=${Math.round(wallHeight)}`, x - 35, wallY + wallHeight / 2);
    });
    
    // Legend
    ctx.fillStyle = '#eaeaea';
    ctx.font = '12px Arial';
    ctx.fillText('Perspective: hauteur = 300 / distance', 10, 25);
}

// ========== INITIALIZE ALL CANVASES ========== 
document.addEventListener('DOMContentLoaded', function() {
    // Draw canvas 1
    setTimeout(drawRaycastingConcept, 100);
    
    // Draw canvas 2
    setTimeout(drawDDAVisualization, 150);
    
    // Draw canvas 3 if exists
    setTimeout(drawWallHeightDiagram, 200);
    
    // Redraw on window resize
    window.addEventListener('resize', function() {
        drawRaycastingConcept();
        drawDDAVisualization();
        drawWallHeightDiagram();
    });
});

// ========== SMOOTH SCROLL NAVIGATION ========== 
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            target.scrollIntoView({
                behavior: 'smooth'
        });
        }
    });
});

// ========== FAQ TOGGLE ========== 
document.querySelectorAll('.faq-item h4').forEach(header => {
    header.addEventListener('click', function() {
        const item = this.parentElement;
        const paragraph = item.querySelector('p');
        
        if (paragraph.style.display === 'none') {
            paragraph.style.display = 'block';
            this.style.color = '#4fc3f7';
        } else {
            paragraph.style.display = 'none';
            this.style.color = '#e94560';
        }
    });
});

// ========== HIGHLIGHT CODE ON HOVER ========== 
document.querySelectorAll('pre').forEach(block => {
    block.addEventListener('mouseenter', function() {
        this.style.boxShadow = 'inset 0 0 10px rgba(233, 69, 96, 0.3)';
    });
    
    block.addEventListener('mouseleave', function() {
        this.style.boxShadow = 'inset 0 2px 5px rgba(0, 0, 0, 0.5)';
    });
});

// ========== ACTIVE NAVIGATION LINK ========== 
window.addEventListener('scroll', function() {
    const sections = document.querySelectorAll('.section, .hero');
    const navLinks = document.querySelectorAll('.nav-links a');
    
    let current = '';
    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        if (pageYOffset >= sectionTop - 200) {
            current = section.getAttribute('id');
        }
    });
    
    navLinks.forEach(link => {
        link.classList.remove('active');
        if (link.getAttribute('href').slice(1) === current) {
            link.style.color = '#e94560';
            link.style.borderBottom = '2px solid #e94560';
        } else {
            link.style.color = '#eaeaea';
            link.style.borderBottom = 'none';
        }
    });
});

// ========== CODE COPY FUNCTIONALITY ========== 
document.querySelectorAll('pre').forEach((block, index) => {
    // Create copy button
    const button = document.createElement('button');
    button.className = 'copy-btn';
    button.textContent = '📋 Copier';
    button.style.position = 'absolute';
    button.style.right = '10px';
    button.style.top = '10px';
    button.style.padding = '5px 10px';
    button.style.backgroundColor = '#e94560';
    button.style.color = '#fff';
    button.style.border = 'none';
    button.style.borderRadius = '4px';
    button.style.cursor = 'pointer';
    button.style.fontSize = '12px';
    button.style.opacity = '0';
    button.style.transition = 'opacity 0.3s';
    
    block.style.position = 'relative';
    block.appendChild(button);
    
    // Show button on hover
    block.addEventListener('mouseenter', () => {
        button.style.opacity = '1';
    });
    
    block.addEventListener('mouseleave', () => {
        button.style.opacity = '0';
    });
    
    // Copy functionality
    button.addEventListener('click', () => {
        const text = block.querySelector('code').textContent;
        navigator.clipboard.writeText(text).then(() => {
            button.textContent = '✓ Copié!';
            setTimeout(() => {
                button.textContent = '📋 Copier';
            }, 2000);
        });
    });
});

// ========== TABLE OF CONTENTS (optional) ========== 
function generateTableOfContents() {
    const headings = document.querySelectorAll('.section h2, .subsection h3');
    const toc = document.createElement('div');
    toc.id = 'table-of-contents';
    toc.style.position = 'fixed';
    toc.style.right = '20px';
    toc.style.top = '100px';
    toc.style.backgroundColor = 'rgba(26, 26, 46, 0.9)';
    toc.style.padding = '15px';
    toc.style.borderRadius = '8px';
    toc.style.maxWidth = '200px';
    toc.style.display = 'none';
    toc.style.zIndex = '50';
    toc.style.border = '1px solid #0f3460';
    toc.style.maxHeight = '80vh';
    toc.style.overflowY = 'auto';
    
    const tocTitle = document.createElement('strong');
    tocTitle.textContent = 'Sections';
    tocTitle.style.color = '#e94560';
    tocTitle.style.display = 'block';
    tocTitle.style.marginBottom = '10px';
    toc.appendChild(tocTitle);
    
    headings.forEach(heading => {
        const link = document.createElement('a');
        link.textContent = heading.textContent;
        link.href = '#';
        link.style.display = 'block';
        link.style.color = '#4fc3f7';
        link.style.textDecoration = 'none';
        link.style.fontSize = '12px';
        link.style.marginBottom = '8px';
        link.style.paddingLeft = heading.localName === 'h3' ? '15px' : '0';
        link.style.transition = 'color 0.3s';
        
        link.addEventListener('mouseenter', () => {
            link.style.color = '#e94560';
        });
        link.addEventListener('mouseleave', () => {
            link.style.color = '#4fc3f7';
        });
        
        link.addEventListener('click', (e) => {
            e.preventDefault();
            heading.scrollIntoView({ behavior: 'smooth' });
        });
        
        toc.appendChild(link);
    });
    
    document.body.appendChild(toc);
    
    // Show/hide based on scroll
    const tocToggle = document.createElement('button');
    tocToggle.textContent = '📑';
    tocToggle.style.position = 'fixed';
    tocToggle.style.right = '20px';
    tocToggle.style.bottom = '20px';
    tocToggle.style.width = '50px';
    tocToggle.style.height = '50px';
    tocToggle.style.backgroundColor = '#e94560';
    tocToggle.style.color = '#fff';
    tocToggle.style.border = 'none';
    tocToggle.style.borderRadius = '50%';
    tocToggle.style.cursor = 'pointer';
    tocToggle.style.fontSize = '20px';
    tocToggle.style.zIndex = '49';
    tocToggle.style.transition = 'all 0.3s';
    
    tocToggle.addEventListener('click', () => {
        toc.style.display = toc.style.display === 'none' ? 'block' : 'none';
    });
    
    document.body.appendChild(tocToggle);
}

// Generate TOC on load
document.addEventListener('DOMContentLoaded', generateTableOfContents);

// ========== CONSOLE EASTER EGG ========== 
console.log('%c🎮 Bienvenue au guide du Raycasting 3D!', 'color: #e94560; font-size: 16px; font-weight: bold;');
console.log('%cTous les concepts expliqués en détail', 'color: #4fc3f7; font-size: 12px;');
console.log('%cAlgorithme DDA, structures de données, et rendu 3D', 'color: #27ae60; font-size: 12px;');
